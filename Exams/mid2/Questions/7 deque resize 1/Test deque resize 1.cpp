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

template< typename T >
void testResize4();

template< typename T >
void testResize5();

template< typename T >
void testResize6();

template< typename T >
void testResize7();

template< typename T >
void testResize8();

template< typename T >
void testResize9();

template< typename T >
void testResize10();

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 );

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
/*
*/
   if( sizeof( T ) >= 2 )
      testResize1< T >();

   testResize2< T >();
   testResize3< T >();
   testResize4< T >();
   testResize5< T >();

   testResize6< T >();
   testResize7< T >();
   testResize8< T >();
   testResize9< T >();
   testResize10< T >();
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
void testResize1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = 0; newSize <= dequeSize * mapSize + dequeSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 2:
            if( myOff % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
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
         case 8:
            switch( mapSize )
            {
            case 16:
               if( myOff % 16 == 15 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 32:
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

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = 0; newSize <= 8; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 16 == 15 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            switch( mapSize )
            {
            case 8:
               if( myOff % 64 == 63 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 16:
               if( myOff % 16 == 15 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            }
            break;
         case 4:
         case 8:
            switch( mapSize )
            {
            case 2 * sizeof( T ) :
               if( myOff % 32 == 31 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 4 * sizeof( T ) :
               if( myOff % 64 == 63 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            case 8 * sizeof( T ) :
               if( myOff % 16 == 15 )
                  cout << "There are " << numErrors << " errors\n";
               break;
            }
            break;
         }
      }

   cout << endl;
}

template< typename T >
void testResize3()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = dequeSize * ( mapSize - 1 ); newSize <= dequeSize * mapSize + dequeSize; ++newSize )
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
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 64 / mapSize ) == 64 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( mapSize >= 4 * sizeof( T ) && myOff % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }

   cout << endl;
}

template< typename T >
void testResize4()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = dequeSize * ( mapSize - 1 ); myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = dequeSize * ( mapSize - 1 ); newSize <= dequeSize * mapSize + dequeSize; ++newSize )
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
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 32 / mapSize ) == 32 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( mapSize >= 4 * sizeof( T ) && myOff == dequeSize * mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }

   cout << endl;
}

template< typename T >
void testResize5()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t maxMapSize;
   if( sizeof( T ) <= 2 )
      maxMapSize = 8;
   else
      maxMapSize = 4 * sizeof( T );

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         if( ( sizeof( T ) == 1 && myOff % 8 == 7 ) ||
             ( sizeof( T ) >= 2 && myOff % 32 == 31 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testResize6()
{
   const size_t maxMapSize = 64;
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            for( size_t newSize = 0; newSize <= maxMapSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testResize7()
{
   const size_t maxMapSize = 8 * sizeof( T );
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 64 / mapSize ) == 64 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( mapSize >= 16 && myOff % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }
   }

   cout << endl;
}

template< typename T >
void testResize8()
{
   size_t maxMapSize;
   if( sizeof( T ) <= 2 )
      maxMapSize = 32;
   else
      maxMapSize = 16 * sizeof( T );

   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            for( size_t newSize = 0; newSize <= maxMapSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }
      }

      if( ( sizeof( T ) <= 4 && mapSize == maxMapSize ) ||
          ( sizeof( T ) == 8 && mapSize >= maxMapSize / 4 ) )
          cout << "There are " << numErrors << " errors\n";
   }

   cout << endl;
}

template< typename T >
void testResize9()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize - myOff % dequeSize; ++mySize )
         {
            for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
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
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.resize( newSize );
               deque2.resize( newSize );

               if( !equal( deque1, deque2 ) )
                  numErrors++;
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 64 / mapSize ) == 64 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( mapSize >= 4 * sizeof( T ) && myOff == dequeSize * mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }
   }

   cout << endl;
}

template< typename T >
void testResize10()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );

   size_t numErrors = 0;

   for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
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

      deque1.resize( newSize );
      deque2.resize( newSize );

      if( !equal( deque1, deque2 ) )
         numErrors++;
   }

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t newSize = 0; newSize <= dequeSize * maxMapSize; ++newSize )
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

         deque1.resize( newSize );
         deque2.resize( newSize );

         if( !equal( deque1, deque2 ) )
            numErrors++;
      }
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