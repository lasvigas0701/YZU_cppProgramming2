#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "deque.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testPushFront();

template< typename T >
void testPushFront1();

template< typename T >
void testPushFront2();

template< typename T >
void testPushFront6();

template< typename T >
void testPushFront7();

template< typename T >
void testPushFront8();

template< typename T >
void testPushFront9();

template< typename T >
void testPushFront10();

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 );

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
/*
*/
   testPushFront1< T >();
   testPushFront2< T >();
   testPushFront6< T >();
   testPushFront7< T >();
   testPushFront8< T >();
   testPushFront9< T >();
   testPushFront10< T >();
/*
*/
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
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }

         if( ( mapSize == 8 * sizeof( T ) && myOff % 64 == 63 ) ||
             ( mapSize == 16 * sizeof( T ) && myOff % 32 == 31 ) )
             cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

const size_t maxMapSize = 256;

template< typename T >
void testPushFront2()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testPushFront6()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testPushFront7()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }

         if( ( sizeof( T ) == 1 && mapSize >= 32 && myOff == 7 ) ||
             ( sizeof( T ) >= 2 && mapSize == 256 && myOff == 7 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testPushFront8()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testPushFront9()
{
   const size_t maxMapSize = 128;
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i / dequeSize % mapSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + static_cast< T >( rand() ) % 99;
            deque1.push_front( value );
            deque2.push_front( value );

            if( !equal( deque1, deque2 ) )
               numErrors++;
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( ( mapSize >= 32 && myOff == dequeSize * ( mapSize - 1 ) - 1 ) ||
                ( mapSize >= 32 && myOff == dequeSize * mapSize - 1 ) ||
                ( mapSize >= 32 && myOff == dequeSize * ( mapSize + 1 ) - 1 ) )
                cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
         case 4:
         case 8:
            if( mapSize == 128 && myOff == dequeSize * ( mapSize + 1 ) - 1 )
                cout << "There are " << numErrors << " errors\n";
         }
      }
   }

   cout << endl;
}

template< typename T >
void testPushFront10()
{
   size_t numErrors = 0;

   {
      std::deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

      deque< T > deque2;
      T ***map2 = reinterpret_cast< T *** > ( &deque2 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

      *mapSize1 = 0;
      *mapSize2 = 0;
      *myOff1 = 0;
      *myOff2 = 0;
      *mySize1 = 0;
      *mySize2 = 0;

      T value = 1 + static_cast< T >( rand() ) % 99;
      deque1.push_front( value );
      deque2.push_front( value );

      if( !equal( deque1, deque2 ) )
         numErrors++;
   }

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      std::deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

      deque< T > deque2;
      T ***map2 = reinterpret_cast< T *** > ( &deque2 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

      *mapSize1 = mapSize;
      *mapSize2 = mapSize;
      *map1 = new T*[ mapSize ]();
      *map2 = new T*[ mapSize ]();
      *myOff1 = 0;
      *myOff2 = 0;
      *mySize1 = 0;
      *mySize2 = 0;

      T value = 1 + static_cast< T >( rand() ) % 99;
      deque1.push_front( value );
      deque2.push_front( value );

      if( !equal( deque1, deque2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 )
{
   T **map1 = *( reinterpret_cast< T *** > ( &deque1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &deque1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 4 );

   T **map2 = *( reinterpret_cast< T *** > ( &deque2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

   if( mapSize1 != mapSize2 )
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

   if( myOff1 != myOff2 )
      return false;

   if( mySize1 != mySize2 )
      return false;

   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t row, col;
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
   {
      row = ( i / dequeSize ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % dequeSize;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}