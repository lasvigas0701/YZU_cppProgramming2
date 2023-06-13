#include <iostream>
using std::cout;
using std::exit;

//#include <algorithm>
//using std::max;

#include "string.h" // include definition of class String

string::string()
    : bx(),
        mySize( 0 ),
        myRes( 15 )
{
}

// from buffer constructor
// Copies the first "count" characters from the array of characters pointed by ptr.
string::string( const char *const ptr, const size_type count )
    : bx(),
        mySize( 0 ),
        myRes( 15 )
{
    mySize = count;
    myRes = ( mySize / 16 ) * 16 + 15;

    /*results same as 39~43
    if (myRes == 15) /*or if (mySize <= 15)
        for (size_type i = 0; i < count; i++) 
            bx.buf[i] = ptr[i];

    else {
        bx.ptr = new value_type[count + 1]();
        for (size_type i = 0; i < count; i++) 
            bx.ptr[i] = ptr[i];
    }
    */

    if (myRes > 15)
        bx.ptr = new value_type[count + 1]();

        for (size_type i = 0; i < count; i++)
            myPtr()[i] = ptr[i];

}

// fill constructor
// Fills the string with "count" consecutive copies of character ch.
string::string( const size_type count, const char ch )
    : bx(),
        mySize( 0 ),
        myRes( 15 )
{
    // construct from count * ch
    mySize = count;
    if( count > 15 )
    {
        myRes = ( mySize / 16 ) * 16 + 15;
        delete[] bx.ptr;
        bx.ptr = new value_type[count + 1];
    }

    /*for (size_type i = 0; i < count; i++)
        myPtr()[i] = ch;*/

    for (iterator p = myPtr(); p < myPtr() + count; p++)
        *p = ch;
}

// copy constructor
// Constructs a copy of "right".
string::string( const string &right )
    : bx(),
        mySize( 0 ),
        myRes( 15 )
{
    mySize = right.mySize;
    myRes = ( mySize / 16 ) * 16 + 15;

    if (myRes > 15)
        bx.ptr = new value_type[mySize + 1]();
        /*for (size_type i = 0; i <= mySize; i++)
            bx.ptr[i] = right.bx.ptr[i];
    }
    else {
        for (size_type i = 0; i <= mySize; i++)
            bx.buf[i] = right.bx.buf[i];
    }*/
    for (size_type i = 0; i < mySize; i++)
        myPtr()[i] = right.myPtr()[i];
}

string::~string()
{
    if( myRes > 15 )
        delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
    if( myRes < 16 )
        return bx.buf;
    else
        return bx.ptr;
}

const string::value_type* string::myPtr() const
{
    if( myRes < 16 )
        return bx.buf;
    else
        return bx.ptr;
}

// String assignment
// Assigns a new value to the string, replacing its current contents.
string& string::assign( const string &right )/*right is str2 in ppt*/
{
    if( this != &right )
    {
        if (right.mySize > myRes)
        {
            if(myRes > 15) /*myRes has minimum value 15 (bx.buf), no bx.ptr*/
                delete[] bx.ptr;

            myRes = myRes * 3 / 2;
            if( myRes < ( right.mySize / 16 ) * 16 + 15 )
                myRes = ( right.mySize / 16 ) * 16 + 15;

            //if (myRes > 15) /*This myRes is new, different from line 118*/
                bx.ptr = new value_type[myRes + 1]();
        }

        for (size_type i = 0; i <= right.mySize; i++)
            myPtr()[i] = right.myPtr()[i];

        mySize = right.mySize;
    }
    return *this;
}

// insert ch at where
string::iterator string::insert( const_iterator where, const char ch )
{
    if( where >= myPtr() && where <= myPtr() + mySize )
    {
        if( mySize == myRes )
        {
            /*cout << "\nCase1: \t";*/
            size_type newMyRes;
            if( myRes == 15 || myRes == 31 )
            newMyRes = myRes + 16;
            else
            newMyRes = myRes * 3 / 2;

            size_type here = where - myPtr(); /*The index of "where" in this string*/
            /*pointer tmp = myPtr(); why cannot -> bx.ptr & bx.buf use the same address?*/
            string tmp(*this); /*store original string*/
            bx.ptr = new value_type[newMyRes + 1](); /*Expand myRes, must new a dynamical array*/

            /*results same as 163~168
            for (size_type i = 0; i < here; i++)
                bx.ptr[i] = tmp.at(i) /*or tmp.myPtr()[i];
            bx.ptr[here] = ch;
            for (size_type i = here + 1; i <= mySize; i++)
                bx.ptr[i] = tmp.myPtr()[i - 1] /*or tmp.at(i - 1);*/

            iterator t = tmp.myPtr(), p = bx.ptr;
            for (; t < tmp.myPtr() + here; t++, p++)
                *p = *t;
            *p++ = ch;
            for (; t < tmp.myPtr() + mySize; t++, p++)
                *p = *t;
            
            myRes = newMyRes;
            mySize++;
            return myPtr() + here;
        }
        else
        {
            /*cout << "\nCase2:\t";*/
            for (size_type i = mySize; i > where - myPtr(); i--)
                myPtr()[i] = myPtr()[i - 1];
            myPtr()[where - myPtr()] = ch;
            mySize++;
            return iterator(where);
        }
    }
    else
        return iterator( nullptr );
}

// Erases the character pointed by where.
string::iterator string::erase( const_iterator where )
{
    if( where >= myPtr() && where < myPtr() + mySize )
    {
        /*results same as 198~199
        size_type here = where - myPtr();
        for (iterator i = myPtr() + here; i < myPtr() + mySize; i++)
            *i = *(i + 1);*/

        for (size_type i = where - myPtr(); i < mySize; i++)
            myPtr()[i] = myPtr()[i + 1];

        mySize--;
        return iterator(where); /*not sure*/
    }
    else
        return iterator( nullptr );
}

void string::clear()
{
    mySize = 0;
    myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
    return myPtr();
}

string::const_iterator string::begin() const
{
    return const_iterator( myPtr() );
}

string::iterator string::end()
{
    return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
    return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
    if( off > mySize )
    {
        cout << "string subscript out of range\n";
        exit( 1 );
    }

    return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
    if( off > mySize )
    {
        cout << "string subscript out of range\n";
        exit( 1 );
    }

    return myPtr()[ off ];
}

string::reference string::front()
{
    return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
    return myPtr()[ 0 ];
}

string::reference string::back()
{
    return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
    return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
    return myPtr();
}

string::size_type string::size() const
{
    return mySize;
}

string::size_type string::capacity() const
{
    return myRes;
}

bool string::empty() const
{
    return mySize == 0;
}