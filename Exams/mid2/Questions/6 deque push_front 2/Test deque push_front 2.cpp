#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "deque.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testPushFront();

template< typename T >
void testPushFront1(); // size > 0

template< typename T >
void testPushFront2(); // size == 0, thus off == 0

template< typename T >
void testPushFront3(); // size == 0, thus off == 0

int main()
{
   testPushFront< char >();

   testPushFront< short >();

   testPushFront< long >();

   testPushFront< long long >();

   system( "pause" );
}

template< typename T >
void testPushFront()
{
   testPushFront1< T >();
   testPushFront2< T >();
   testPushFront3< T >();
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testPushFront1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   const size_t maxMapSize = 16 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSize;
            *map1 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *mySize1 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = 1 + rand() % 99;
            }

            deque1.push_front( 1 + rand() % 99 );

            T ***map2 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            if( ( *myOff2 + 1 ) % ( dequeSize * mapSize ) != myOff )
               numErrors++;

            if( *mySize2 != mySize + 1 )
               numErrors++;

            if( *mapSize2 == mapSize )
               if( *map2 != *map1 )
                  numErrors++;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               if( ( *map2 )[ block % mapSize ] != ( *map1 )[ block % mapSize ] )
                  numErrors++;
         }

         switch( sizeof( T ) )
         {
         case 1:
         case 2:
         case 4:
            if( ( mapSize == 8 * sizeof( T ) && myOff == dequeSize * mapSize / 2 - 1 ) ||
                ( mapSize == 16 * sizeof( T ) && myOff == dequeSize * mapSize / 2 - 1 ) )
                cout << "There are " << numErrors << " errors\n";
            break;
         case 8:
            if( ( mapSize == 64 && myOff == dequeSize * mapSize / 2 - 1 ) ||
                ( mapSize == 128 && myOff % ( dequeSize * mapSize / 4 ) == dequeSize * mapSize / 4 - 1 ) )
                cout << "There are " << numErrors << " errors\n";
         }
      }

   cout << endl;
}

template< typename T >
void testPushFront2()
{
   size_t numErrors = 0;
   deque< T > deque1;
   T ***map1 = reinterpret_cast< T *** > ( &deque1 );
   size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
   size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

   *mapSize1 = 0;
   *myOff1 = 0;
   *mySize1 = 0;

   deque1.push_front( 1 + rand() % 99 );

   T ***map2 = reinterpret_cast< T *** > ( &deque1 );
   size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
   size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

   if( *myOff2 != 8 * compDequeSize< T >() - 1 )
      numErrors++;

   if( *mySize2 != 1 )
      numErrors++;

   if( *mapSize2 == 8 )
      if( *map2 != *map1 )
         numErrors++;

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testPushFront3()
{
   size_t numErrors = 0;
   const size_t maxMapSize = 512;
   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      *mapSize1 = mapSize;
      *map1 = new T*[ mapSize ]();
      *myOff1 = 0;
      *mySize1 = 0;

      deque1.push_front( 1 + rand() % 99 );

      T ***map2 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      if( *myOff2 != mapSize * compDequeSize< T >() - 1 )
         numErrors++;

      if( *mySize2 != 1 )
         numErrors++;

      if( *mapSize2 == mapSize )
         if( *map2 != *map1 )
            numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}