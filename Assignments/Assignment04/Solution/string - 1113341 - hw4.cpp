// string class member-function definitions.

#include <iostream>
using std::cout;
using std::endl;

#include "string.h" // string class definition

string::string()
    : myData()
{
}

// from buffer
// Copies the first "count" characters from the array of characters pointed by ptr.
string::string( const value_type * const ptr, const size_type count )
    : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.myRes > 15)
        myData.bx.ptr = new value_type[myData.myRes + 1]();
    for (size_type i = 0; i < count; i++)
        myData.myPtr()[i] = ptr[i];
}
// fill constructor
// Fills the string with "count" consecutive copies of character ch.
string::string( const size_type count, const value_type ch )
    : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.myRes > 15)
        myData.bx.ptr = new value_type[myData.myRes];

    for (iterator p = myData.myPtr(); p < myData.myPtr() + count; p++)
        *p = ch;
}

// copy constructor
// Constructs a copy of "right".
string::string( const string &right )
    : myData()
{
    myData.mySize = right.myData.mySize;
    myData.myRes = right.myData.myRes;

    if (myData.myRes > 15)
        myData.bx.ptr = new value_type[myData.myRes + 1];

    for (size_t i = 0; i < myData.mySize; i++)
        myData.myPtr()[i] = right.myData.myPtr()[i];
}

string::~string()
{
    if( myData.myRes > 15 )
        delete[] myData.bx.ptr;
}

string& string::operator=( const string &right )
{
    if( this != &right )
    {
        if( right.myData.mySize > myData.myRes )
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;

            myData.myRes = myData.myRes * 3 / 2;
            if( myData.myRes < ( right.myData.mySize / 16 ) * 16 + 15 )
                myData.myRes = ( right.myData.mySize / 16 ) * 16 + 15;

            /*minimum of myRes is 15, if right.mySize > myRes, must use bx.ptr*/
            myData.bx.ptr = new value_type[myData.myRes + 1]();
        }
        for (size_type i = 0; i < right.myData.mySize; i++)
            *(myData.myPtr() + i) = *(right.myData.myPtr() + i);
        myData.mySize = right.myData.mySize;
    }
    return *this;
}

string& string::operator=( const value_type * const ptr )
{
    size_t count = strlen( ptr );
    if( count > 0 )
    {
        if( count > myData.myRes )
        {
            if (myData.myRes > 15)
                delete[] myData.bx.ptr;

            myData.myRes = myData.myRes * 3 / 2;
            if( myData.myRes < ( count / 16 ) * 16 + 15 )
                myData.myRes = ( count / 16 ) * 16 + 15;

            myData.bx.ptr = new value_type[myData.myRes + 1]();
        }
        for (size_t i = 0; i < count; i++)
            *(myData.myPtr() + i) = *(ptr + i);
        myData.mySize = count;
    }




    return *this;
}

string& string::erase( size_t off, size_t count )
{
    if( off < myData.mySize )
    {
        if (off + count> myData.mySize) /*if which need to be delete is more than size(), delete the rest of sourceLine*/
            myData.mySize = off;
        else {
            for (size_t i = off; i < myData.mySize; i++) {
                myData.myPtr()[i] = myData.myPtr()[i + count];
                /*why can if myData.myPtr()[i + count] is out of the string* /
                //if (i == myData.mySize) /*the last character has been remove to where it should be after erasing*/
                //    break;
            }
            myData.mySize -= count;
        }
    }
    return *this;
}

void string::clear()
{
    myData.mySize = 0;
    myData.myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
    return iterator( myData.myPtr() );
}

string::const_iterator string::begin() const
{
    return const_iterator( myData.myPtr() );
}

string::iterator string::end()
{
    return iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::const_iterator string::end() const
{
    return const_iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::reference string::operator[]( size_type off )
{
    // check for off out-of-range error
    if( off > myData.mySize )
    {
        //cout << "off" << off << endl;
        //cout << "size: " << myData.mySize << endl;
        //cout << off << endl;
        //cout << myData.myPtr()[myData.mySize - 1] << endl;
        cout << "\nstring subscript out of range\n";
        system( "pause" );
        exit( 1 ); // terminate program; off out of range
    }

    return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_reference string::operator[]( size_type off ) const
{
    // check for off out-of-range error
    if( off > myData.mySize )
    {
        //cout << "off" << off << endl;
        //cout << "size: " << myData.mySize << endl;
        //cout << myData.myPtr()[myData.mySize - 1] << endl;
        cout << "\nstring subscript out of range\n";
        system( "pause" );
        exit( 1 ); // terminate program; off out of range
    }

    return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_pointer string::data() const
{
    return myData.myPtr();
}

string::size_type string::size() const
{
    return myData.mySize;
}

string::size_type string::find( value_type ch, size_type off ) const
{
    for (size_t i = off; i < myData.mySize; i++)
    {
        //cout << "hello" << myData.myPtr()[i];
        if (myData.myPtr()[i] == ch)
            return i;
    }

    return string::npos;
}

string::size_type string::find( const value_type *ptr, size_type off ) const
{
    bool found = false;
    for (size_t i = off; i < myData.mySize; i++)
    {
        if (*(myData.myPtr() + i) == *(ptr)) {/*If there is a char in *this match with the first of ptr*/
            found = true; /*Assume that it is match, then continue to check~*/
            for (size_t j = i, p = 0; p < strlen(ptr); j++, p++) /*Check whether the rest of sourceLine is match to ptr*/
                if (*(myData.myPtr() + j) != *(ptr + p)) /*~until not match*/
                {
                    found = false;
                    i += strlen(ptr); /*If found is false means they are not match between i to i + strlen(ptr)*/
                    break;
                }
        }
        if (found)
            return i;
    }
    return string::npos;
}

string string::substr( size_type off, size_type count ) const
{
    //cout << "off: " << off << "  " << count << std::endl;
    string token;
    token.myData.mySize = (off + count) < myData.mySize ? count : (myData.mySize - off); /*total : the end of string*/
    token.myData.myRes = (token.myData.mySize / 16) * 16 + 15;
    token = new value_type[token.myData.myRes]();
    for (size_t t = 0, s = off ; t < token.size(); t++, s++) {
        //cout << off + i;
        //cout << token.myData.mySize;
        (token.myData.myPtr()[t]) = (myData.myPtr()[s]);
        //cout << token.myData.myPtr()[i];
    }
    return token;
}

// compare [ 0, size() ) with right for equality
bool string::equal( const string &right ) const
{
    if (size() != right.size())
        return false;

    for (size_type i = 0; i < size(); i++)
        if (myData.myPtr()[i] != right.myData.myPtr()[i])
            return false;

    return true;
}

bool operator==( const string &left, const string &right )
{
    return left.equal( right );
//   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=( const string &left, const string &right )
{
    return !left.equal( right );
}

ostream& operator<<( ostream &ostr, string &str )
{
    for( size_t i = 0; i < str.size(); i++ )
        ostr << str.data()[ i ];

    return ostr; // enables cout << x << y;
}