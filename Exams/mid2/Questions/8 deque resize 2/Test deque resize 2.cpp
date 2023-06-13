#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <deque>
#include "deque.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testResize();

template< typename T >
void testResize1();

template< typename T >
void testResize2();

template< typename T >
void testResize3();

int main()
{
   testResize< char >();

   testResize< short >();

   testResize< long >();

   testResize< long long >();

   system( "pause" );
}

template< typename T >
void testResize()
{
   time_t t = time( nullptr );

   testResize1< T >();

   testResize2< T >();

   testResize3< T >();
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testResize1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = 0; newSize <= dequeSize * mapSize + dequeSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );

               T ***map2 = reinterpret_cast< T *** > ( &deque1 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

               if( newSize == 0 )
               {
                  if( *myOff2 != 0 )
                     numErrors++;
               }
               else
               {
                  if( *myOff2 != myOff )
                     numErrors++;
               }

               if( *mySize2 != newSize )
                  numErrors++;

               if( newSize <= mySize )
               {
                  if( *mapSize2 != mapSize )
                     numErrors++;

                  if( *map2 != *map1 )
                     numErrors++;

                  for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
                     if( ( *map2 )[ block % mapSize ] != ( *map1 )[ block % mapSize ] )
                        numErrors++;
               }
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            switch( mapSize )
            {
            case 8:
               if( myOff % 32 == 31 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 16:
               if( myOff % 8 == 7 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            }
            break;
         case 4:
            switch( mapSize )
            {
            case 16:
               if( myOff % 32 == 31 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 32:
               if( myOff % 8 == 7 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            }
            break;
         case 8:
            switch( mapSize )
            {
            case 16:
               if( myOff % 32 == 31 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 32:
               if( myOff % 32 == 31 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 64:
               if( myOff % 4 == 3 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            }
            break;
         }
      }

   cout << endl;
}

template< typename T >
void testResize2()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );

   size_t numErrors = 0;

   for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
   {
      deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      *mapSize1 = 0;
      *myOff1 = 0;
      *mySize1 = 0;

      deque1.resize( newSize );

      T ***map2 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      if( *myOff2 != 0 )
         numErrors++;

      if( *mySize2 != newSize )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testResize3()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
      {
         deque< T > deque1;
         T ***map1 = reinterpret_cast< T *** > ( &deque1 );
         size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
         size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
         size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

         *mapSize1 = mapSize;
         *map1 = new T * [ mapSize ]();
         *myOff1 = 0;
         *mySize1 = 0;

         deque1.resize( newSize );

         T ***map2 = reinterpret_cast< T *** > ( &deque1 );
         size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
         size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
         size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

         if( *myOff2 != 0 )
            numErrors++;

         if( *mySize2 != newSize )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}