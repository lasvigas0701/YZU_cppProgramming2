// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <deque>
using std::deque;

#include <string>
using std::string;


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   HugeInteger( string str );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square(); // the square of HugeInteger
   HugeInteger squareRoot(); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
   const value_type tenMillion = 10000000;
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

template< typename T >
HugeInteger< T >::HugeInteger( string str )
{
   value_type digits[ 1001 ] = {};
   size_type last = str.size() - 1;
   for( size_type i = 0; i <= last; ++i )
      digits[ i ] = static_cast< value_type >( str[ last - i ] ) - '0';

   size_type numDigits = sizeof( value_type ) - 1;
   for( size_type i = 0; i <= last; i += numDigits )
   {
      value_type bigDigit = digits[ i ] +
                           digits[ i + 1 ] * 10 +
                           digits[ i + 2 ] * 100 +
                           digits[ i + 3 ] * 1000 +
                           digits[ i + 4 ] * 10000 +
                           digits[ i + 5 ] * 100000 +
                           digits[ i + 6 ] * 1000000;

      integer.push_back( bigDigit );
   }
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{



} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square()
{
   HugeInteger zero;
   if( isZero() )
      return zero;



}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot()
{
   HugeInteger zero;
   if( isZero() )
      return zero;



}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   output << *it;
   for( ++it; it != hugeInteger.integer.rend(); ++it )
      output << setw( numDigits ) << setfill( '0' ) << *it;

   return output; // enables cout << x << y;
}

template< typename T1, typename T2 >
void solution()
{
   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      string str;
      cin >> str;

      HugeInteger< T1 > hugeInteger( str );

      cout << hugeInteger.squareRoot() << endl;

      if( i < numCases )
         cout << endl;
   }
}

int main()
{
   // execute the following 3 instructions one by one, each of them should get an AC
//   solution< vector< long long int >, long long int >();
//   solution< list< long long int >, long long int >();
   solution< deque< long long int >, long long int >();

   system( "pause" );
}