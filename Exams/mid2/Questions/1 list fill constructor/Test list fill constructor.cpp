// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list.h" // include definition of class template list

template< typename T >
void testFillConstructor();

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right );

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testFillConstructor< char >();
   testFillConstructor< short >();
   testFillConstructor< long >();
   testFillConstructor< long long >();

   system( "pause" );
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

const int number = 500;

template< typename T >
void testFillConstructor()
{
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      if( !equal( list1, list2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right )
{
   if( left.size() != right.size() ) // different number of elements
      return false;

   if( right.size() == 0 )
      return true;

   typename list< T >::iterator it1 = left.begin();
   typename std::list< T >::iterator it2 = right.begin();
   for( ; it2 != right.end(); it1 = ++it1, ++it2 )
      if( *it1 != *it2 )
         return false;

   return true;
}