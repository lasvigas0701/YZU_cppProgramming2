#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstdlib>
using std::srand;
using std::rand;

#include <string>
using std::string;

#include <ctime>
using std::time;

class VectorVal
{
public:
    using value_type = int;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    VectorVal()
        : myFirst(),
        myLast(),
        myEnd()
    {
    }

    pointer myFirst; // pointer to beginning of array
    pointer myLast;  // pointer to current end of sequence
    pointer myEnd;   // pointer to end of array
};


class vector // varying size array of values
{
public:
    using value_type = int;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = int &;
    using const_reference = const int &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

private:
    using ScaryVal = VectorVal;

public:
    using iterator = value_type *;
    using const_iterator = const value_type *;

    // empty container constructor (default constructor)
    // Constructs an empty container, with no elements.
    vector()
        : myData()
    {
    }

    // fill constructor
    // Constructs a container with "count" elements.
    // Each element is initialized as 0.
    vector( const size_type count )
        : myData()
    {
        if( count != 0 )
        {
            myData.myFirst = new value_type[ count ]();
            myData.myLast = myData.myFirst + count;
            myData.myEnd = myData.myFirst + count;
        }
    }

    // copy constructor
    // Constructs a container with a copy of each of the elements in "right",
    // in the same order.
    vector( const vector &right )
        : myData()
    {
        size_type count = right.myData.myLast - right.myData.myFirst;
        myData.myFirst = new value_type[count]();
        for (size_type i = 0; i < count; i++)
            myData.myFirst[i] = right.myData.myFirst[i];

        myData.myEnd = myData.myLast = myData.myFirst + count;
    }

    // Vector destructor
    // Destroys the container object.
    // Deallocates all the storage capacity allocated by the vector.
    ~vector()
    {
        if( myData.myFirst != nullptr )
            delete[] myData.myFirst;
    }

    // overloaded assignment operator
    // Assigns new contents to the container, replacing its current contents,
    // and modifying its size accordingly.
    // Copies all the elements from "right" into the container
    // (with "right" preserving its contents).
    vector& assign( const vector &right )
    {
        if( this != &right ) // avoid self-assignment
        {
            size_type rightSize = right.size();
            if( rightSize > capacity() )
            {
                if( size() > 0 )
                    delete[] myData.myFirst; // release space

                size_type newCapacity = capacity() * 3 / 2;
                if( newCapacity < rightSize )
                    newCapacity = rightSize;

                myData.myFirst = new value_type[newCapacity]();
                myData.myEnd = myData.myFirst + newCapacity;
            }

            for (iterator p = myData.myFirst, r = right.myData.myFirst; r < right.myData.myLast; p++, r++)
                *p = *r;

            myData.myLast = myData.myFirst + rightSize;
        }

        return *this; // enables x = y = z, for example
    }

    bool equal( const vector &right ) const
    {
        if (size() != right.size())
            return false;

        for (size_type i = 0; i < size(); i++)
            if (*(myData.myFirst + i) != *(right.myData.myFirst + i))
                return false;

        return true;
    }

    // The vector is extended by inserting a new element before the element
    // at the specified position, effectively increasing the container size by one.
    // This causes an automatic reallocation of the allocated storage space
    // if and only if the new vector size surpasses the current vector capacity.
    // Relocates all the elements that were after "where" to their new positions.
    iterator insert( const_iterator where, const value_type &val )
    {
        if( where >= myData.myFirst && where <= myData.myLast )
        {
            size_type originalSize = size();
            size_type originalCapacity = capacity();
            if( originalSize == originalCapacity )
            {
                size_type newCapacity;
                if( originalCapacity <= 1 )
                    newCapacity = originalCapacity + 1;
                else
                    newCapacity = originalCapacity * 3 / 2;
                
                size_t here = where - myData.myFirst, last = myData.myLast - myData.myFirst; /*index of where and myLast*/
                pointer tmp = myData.myFirst;
                myData.myFirst = new value_type[newCapacity]();
                iterator p = myData.myFirst, t = tmp; /*pointers to do iteration and modify value*/
                
                for (size_t i = 0; i < here; i++)
                    *(p + i) = *(t + i);
                *(p + here) = val;
                for (size_t i = here + 1; i <= last; i++)
                    *(p + i) = *(t + i - 1);

                myData.myEnd = myData.myFirst + newCapacity;
                myData.myLast = myData.myFirst + last + 1;
          
                delete[] tmp;
                return myData.myFirst + here;
            }
            else
            {
                iterator p = myData.myLast;
                for (; p > where; p--)
                    *p = *(p - 1); /*Assign the former one to the latter adjacent one from myLast to where*/
                *p = val; /*Assign val to where*/

                myData.myLast++; 
                
                return (iterator)where;
            }
        }
        else
            return nullptr;
    }

    // Removes from the vector either a single element (where).
    // This effectively reduces the container size by one, which is destroyed.
    // Relocates all the elements after the element erased to their new positions.
    iterator erase( const_iterator where )
    {
        if( where >= myData.myFirst && where < myData.myLast )
        {
            size_type count = where - myData.myFirst;

            for (size_type i = count; i < size() - 1; i++) /*From where to myLast - 1*/
                myData.myFirst[i] = myData.myFirst[i + 1]; /*Assign the latter one to the former one*/

            myData.myLast--;
            return (iterator) where;
        }
        else
            return nullptr;
    }

    // Removes all elements from the vector (which are destroyed),
    // leaving the container with a size of 0.
    // A reallocation is not guaranteed to happen,
    // and the vector capacity is not guaranteed to change due to calling this function.
    void clear() // erase all
    {
        myData.myLast = myData.myFirst;
    }

    // Returns an iterator pointing to the first element in the vector.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    iterator begin()
    {
        return myData.myFirst;
    }

    // Returns an iterator pointing to the first element in the vector.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    const_iterator begin() const
    {
        return const_iterator( myData.myFirst );
    }

    // Returns an iterator referring to the past-the-end element in the vector container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the vector.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as vector::begin.
    iterator end()
    {
        return myData.myLast;
    }

    // Returns an iterator referring to the past-the-end element in the vector container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the vector.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as vector::begin.
    const_iterator end() const
    {
        return const_iterator( myData.myLast );
    }

    // Returns whether the vector is empty (i.e. whether its size is 0).
    bool empty() const
    {
        return myData.myFirst == myData.myLast;
    }

    // Returns the number of elements in the vector.
    // This is the number of actual objects held in the vector,
    // which is not necessarily equal to its storage capacity.
    size_type size() const
    {
        return static_cast< size_type >( myData.myLast - myData.myFirst );
    }

    // Returns the size of the storage space currently allocated for the vector,
    // expressed in terms of elements.
    // This capacity is not necessarily equal to the vector size.
    // It can be equal or greater, with the extra space allowing to accommodate
    // for growth without the need to reallocate on each insertion.
    size_type capacity() const
    {
        return static_cast< size_type >( myData.myEnd - myData.myFirst );
    }

private:
    ScaryVal myData;
};


class HugeInteger
{
public:
    HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

    // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
    HugeInteger( const HugeInteger &integerToCopy );

    // Constructs a HugeInteger with str.size() elements.
    // Each element is initialized as the correcponding element in str.
    HugeInteger( string str );

    ~HugeInteger(); // destructor; destroys the HugeInteger

    const HugeInteger& assign( const HugeInteger &right ); // assignment operator

    bool equal( const HugeInteger &right ) const; // less than or equal to

    bool less( const HugeInteger &right ) const; // less than

    HugeInteger square(); // return the square of HugeInteger

    HugeInteger squareRoot(); // return the square root of HugeInteger

    bool isZero() const; // return true if and only if all digits are zero

    void print(); // print a HugeInteger
private:
    vector integer;
    const int thousand = 1000;
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
    : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
    : integer( integerToCopy.integer )
{
}

// Constructs a HugeInteger with right.size() elements.
// Each element is initialized as the correcponding element in right.
HugeInteger::HugeInteger( string str )
{
    int digits[ 1011 ] = {};
    size_t last = str.size() - 1;
    for( size_t i = 0; i <= last; ++i )
        digits[ i ] = static_cast< int >( str[ last - i ] ) - '0';

    for( size_t i = 0; i <= last; i += 3 )
    {
        int bigDigit = digits[ i ] + digits[ i + 1 ] * 10 + digits[ i + 2 ] * 100;

        integer.insert( integer.end(), bigDigit );
    }
}

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
    if( &right != this ) // avoid self-assignment
        integer.assign( right.integer );

    return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
    return integer.equal( right.integer );
}

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
    if (integer.size() < right.integer.size()) /*this->integer.size < right.integer.size*/
        return true;
    else if (integer.size() == right.integer.size()) { /*Iteration to compare*/
        vector::const_iterator p = integer.begin(), r = right.integer.begin();

         for (int i = integer.size() - 1; i >= 0; i--) {
             if (*(p + i) > *(r + i))
                return false;
             else if (*(p + i) < *(r + i))
                return true;
         }
    }
    return false;
}

HugeInteger HugeInteger::square()
{
    HugeInteger zero;
    if( isZero() )
        return zero;
    size_t size = integer.size();
    HugeInteger squr(size * 2);
    vector::iterator sq = squr.integer.begin(), p = integer.begin(); /*pointers represent starting addresses*/

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            *(sq + i + j) += *(p + i) * *(p + j);

    /*same as 404 ~ 406
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            squr.integer.begin()[i + j] += integer.begin()[i] * integer.begin()[j];*/

    for (int i = 0; i < size * 2 - 1; i++) { /*(size * 2 - 1) is squr.integer.size()-1*/
        if (*(sq + i) > 999) {
            *(sq + i + 1) += *(sq + i) / 1000;
            *(sq + i) %= 1000;
        }
    }

    /*same as 413~418
    for (int i = 0; i < size * 2 - 1; i++) {
        if (squr.integer.begin()[i] > 999) {
            squr.integer.begin()[i + 1] += squr.integer.begin()[i] / 1000;
            squr.integer.begin()[i] %= 1000;
        }
    }*/

    if (*(squr.integer.end() - 1) == 0) /*Make sure the size of squr is equal to original hugeInt*/
        squr.integer.erase(squr.integer.end()-1);

    return squr;
}

HugeInteger HugeInteger::squareRoot()
{
    HugeInteger zero;
    if( isZero() )
        return zero;
    size_t size = (integer.size() + 1) / 2;
    HugeInteger sqrt(size);
    
   
   /*for (int i = size - 1; i >= 0; i--) {
        int high = 999, low = 1, middle{};
        while (low <= high) {
            middle = (high + low) / 2;
            sqrt.integer.begin()[i] = middle;

            HugeInteger squr = sqrt.square();

            if (equal(squr))
                return sqrt;
            else if (less(squr)) /* *this less than sqrt
                high = middle - 1;
            else
                low = middle + 1;
        }
        if (less(sqrt.square()))
            sqrt.integer.begin()[i]--;
    }*/
    HugeInteger squr;/*the answer*/
    for (vector::iterator sq = sqrt.integer.end() - 1; sq >= sqrt.integer.begin(); sq--) {
        /*sq means addresses of each index of sqrt(squre root)*/
        int high = 999, low = 1, middle{};
        while (low <= high) {
            middle = (high + low) / 2;
            *sq = middle;

            squr.assign(sqrt.square()); /*avoid repetitive call f(squre()) to save time*/

            if (equal(squr))
                return sqrt;
            else if (less(squr)) /* *this less than sqrt*/
                high = middle - 1;
            else
                low = middle + 1;
        }
        if (less(squr)) {
            cout << "in\n"; (*sq)--;
        }
           
    }
    return sqrt;
}

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
    typename vector::const_iterator it = integer.begin();
    for( ; it != integer.end(); ++it )
        if( *it != 0 )
            return false;

    return true;
}

void HugeInteger::print()
{
    typename vector::iterator it = integer.end() - 1;
    cout << *it;
    for (--it; it != integer.begin() - 1; --it) 
        cout << setw(3) << setfill('0') << *it;

    cout << endl;
}

int main()
{
    int numCases;
    cin >> numCases;
    for( int i = 1; i <= numCases; ++i )
    {
        string str;
        cin >> str;

        HugeInteger hugeInteger( str );

        hugeInteger.squareRoot().print();

        if( i < numCases )
            cout << endl;
    }
}