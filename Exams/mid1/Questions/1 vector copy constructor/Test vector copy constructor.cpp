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
void testCopyConstructor();

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
   testCopyConstructor< T >();
   cout << endl;
}

template< typename T >
void testCopyConstructor()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector< T > vector1( c );
      T *first1 = vector1.begin(); // first1 = vector1.myData.myFirst

      std::vector< T > vector2( c );
      T *first2 = *( reinterpret_cast< T ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         T value = 1 + static_cast< T >( rand() % 99 );
         first1[ i ] = value;
         first2[ i ] = value;
      }

      T **last1 = reinterpret_cast< T ** >( &vector1 ) + 1;
      T **last2 = reinterpret_cast< T ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myData.myLast = vector1.myData.myFirst + s
         *last2 = first2 + s;

         vector< T > vector3( vector1 );
         std::vector< T > vector4( vector2 );

         if( !equal( vector3, vector4 ) )
            numErrors++;
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