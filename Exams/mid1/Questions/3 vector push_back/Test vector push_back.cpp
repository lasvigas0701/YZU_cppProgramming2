// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector.h"

template< typename T >
void testVector();

template< typename T >
void testPushBack1();

template< typename T >
void testPushBack2();

// Determines if two vectors are equal.
template< typename T >
bool equal( vector< T > &left, std::vector< T > &right );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

const int number = 300;

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testVector< char >();
   testVector< short >();
   testVector< long >();
   testVector< long long >();

   system( "pause" );
}

template< typename T >
void testVector()
{
   testPushBack1< T >();
   testPushBack2< T >();
   cout << endl;
}

template< typename T >
void testPushBack1()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector< T > vector1( c );
      std::vector< T > vector2( c );

      T *first1 = vector1.begin(); // first1 = vector1.myData.myFirst
      T *first2 = *( reinterpret_cast< T ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         T value = 1 + static_cast< T >( rand() % 99 );
         first1[ i ] = value;
         first2[ i ] = value;
      }

      T **last1 = reinterpret_cast< T ** >( &vector1 ) + 1;
      // last1 points to vector1.myData.myLast
      T **last2 = reinterpret_cast< T ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myData.myLast = vector1.myData.myFirst + s
         *last2 = first2 + s;

         T value = 1 + static_cast< T >( rand() % 99 );
         vector1.push_back( value );
         vector2.push_back( value );

         if( !equal( vector1, vector2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testPushBack2()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector< T > v( c );
      T *first = v.begin(); // first = v.myData.myFirst
      for( int i = 0; i < c; i++ )
         first[ i ] = 1 + static_cast< T >( rand() % 99 );

      T **last = reinterpret_cast< T ** >( &v ) + 1; // last points to v.myData.myLast
      for( int s = 0; s <= c; s++ )
      {
         *last = first + s; // v.myData.myLast = v.myData.myFirst + s

         T value = 1 + static_cast< T >( rand() % 99 );
         v.push_back( value );

         if( v.capacity() == c && v.begin() != first )
            numErrors++;

         // v.begin() == first if and only if
         // the array pointed by v.myData.myFirst before
         // the excution of v.push_back( value ) is the same as
         // the array pointed by v.myData.myFirst after
         // the excution of v.push_back( value )
         // i.e., there is no memory allocation during the excution of
         // v.push_back( value )
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two vectors are equal.
template< typename T >
bool equal( vector< T > &left, std::vector< T > &right )
{
   if( left.capacity() != right.capacity() )
      return false;

   if( left.size() != right.size() )
      return false;

   if( right.size() == 0 )
      return true;

   for( size_t i = 0; i < right.size(); ++i )
      if( left[ i ] != right[ i ] )
         return false;

   return true;
}