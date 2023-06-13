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
void testAssignment1();

template< typename T >
void testAssignment2();

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
   testAssignment1< T >();
   testAssignment2< T >();
   cout << endl;
}

template< typename T >
void testAssignment1()
{
   const int number = 30;
   int numErrors = 0;
   for( int c1 = 0; c1 <= number; c1++ )
   {
      vector< T > vector1( c1 );
      std::vector< T > vector2( c1 );

      T *first1 = vector1.begin(); // first1 = vector1.myData.myFirst
      T *first2 = *( reinterpret_cast< T ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c1; i++ )
      {
         T value = 1 + static_cast< T >( rand() % 99 );
         first1[ i ] = value;
         first2[ i ] = value;
      }

      T **last1 = reinterpret_cast< T ** >( &vector1 ) + 1;
      // last1 points to vector1.myData.myLast
      T **last2 = reinterpret_cast< T ** >( &vector2 ) + 1 + offset;
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1; // vector1.myData.myLast = vector1.myData.myFirst + s1
         *last2 = first2 + s1;

         for( int c2 = 0; c2 <= number; c2++ )
         {
            vector< T > vector3( c2 );
            std::vector< T > vector4( c2 );

            T *first3 = vector3.begin(); // first3 = vector3.myData.myFirst
            T *first4 = *( reinterpret_cast< T ** >( &vector4 ) + offset );
            // first4 points to the first element of the array in vector4

            for( int i = 0; i < c2; i++ )
            {
               T value = 1 + static_cast< T >( rand() % 99 );
               first3[ i ] = value;
               first4[ i ] = value;
            }

            T **last3 = reinterpret_cast< T ** >( &vector3 ) + 1;
            // last3 points to vector3.myData.myLast
            T **last4 = reinterpret_cast< T ** >( &vector4 ) + 1 + offset;
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               *last3 = first3 + s2; // vector3.myData.myLast = vector3.myData.myFirst + s2
               *last4 = first4 + s2;

               vector3 = vector1;
               vector4 = vector2;

               if( !equal( vector3, vector4 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testAssignment2()
{
   const int n = 40;
   int numErrors = 0;
   for( int c1 = 0; c1 <= n; c1++ )
   {
      vector< T > vector1( c1 );
      T *first1 = vector1.begin(); // first1 = vector1.myData.myFirst
      for( int i = 0; i < c1; i++ )
         first1[ i ] = 1 + static_cast< T >( rand() % 99 );

      T **last1 = reinterpret_cast< T ** >( &vector1 ) + 1;
      // last1 points to vector1.myData.myLast
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1;

         for( int c2 = 0; c2 <= n; c2++ )
         {
            vector< T > vector2( c2 );
            T *first2 = vector2.begin(); // first2 = vector2.myData.myFirst
            for( int i = 0; i < c2; i++ )
               first2[ i ] = 1 + static_cast< T >( rand() % 99 );

            T **last2 = reinterpret_cast< T ** >( &vector2 ) + 1;
            // last2 points to vector2.myData.myLast
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               *last2 = first2 + s2;

               vector2 = vector1;

               if( vector2.capacity() == c2 && vector2.begin() != first2 )
                  numErrors++;
            }
         }
      }
   }

   // vector2.begin() == first2 if and only if
   // the array pointed by vector2.myData.myFirst before
   // the excution of vector2 = vector1 is the same as
   // the array pointed by vector2.myData.myFirst after
   // the excution of vector2 = vector1
   // i.e., there is no memory allocation during the excution of vector2.assign( vector1 )

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