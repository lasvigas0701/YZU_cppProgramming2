#ifndef DEQUE_H
#define DEQUE_H

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
    using size_type = typename MyDeque::size_type;

public:
    using value_type = typename MyDeque::value_type;
    using difference_type = typename MyDeque::difference_type;
    using pointer = typename MyDeque::const_pointer;
    using reference = const value_type &;

    // construct with null pointer
    DequeConstIterator()
        : myOff( 0 ),
        myCont( nullptr )
    {
    }

    // construct with offset off in *pDeque
    DequeConstIterator( size_type off, const MyDeque *pDeque )
        : myOff( off ),
        myCont( pDeque )
    {
    }

    DequeConstIterator( const DequeConstIterator &right ) // copy constructor
        : myOff( right.myOff ),
        myCont( right.myCont )
    {
    }

    ~DequeConstIterator() // destructor
    {
    }

    // const return avoids: ( a1 = a2 ) = a3
    const DequeConstIterator& operator=( const DequeConstIterator &right )
    {
        if( &right != this ) // avoid self-assignment
        {
            myCont = right.myCont;
            myOff = right.myOff;
        }
        return *this; // enables x = y = z, for example
    }

    reference operator*() const
    {
        // elements per block (a power of 2)
        size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

//      size_type block = myOff % ( dequeSize * myCont->mapSize ) / dequeSize;
        size_type block = myCont->getBlock( myOff );
        size_type off = myOff % dequeSize;
        return myCont->map[ block ][ off ];
    }

    pointer operator->() const
    {
        return &( operator*() );
    }

    DequeConstIterator& operator++() // preincrement
    {
        ++myOff;
        return *this;
    }

    DequeConstIterator operator++( int ) // postincrement
    {
        DequeConstIterator tmp = *this;
        ++*this;
        return tmp;
    }

    DequeConstIterator& operator--() // predecrement
    {
        --myOff;
        return *this;
    }

    DequeConstIterator operator--( int ) // postdecrement
    {
        DequeConstIterator tmp = *this;
        --*this;
        return tmp;
    }

    // increment by integer
    DequeConstIterator& operator+=( const difference_type off )
    {
        myOff += off;
        return *this;
    }

    // return this + integer
    DequeConstIterator operator+( const difference_type off ) const
    {
        DequeConstIterator tmp = *this;
        return tmp += off;
    }

    // decrement by integer
    DequeConstIterator& operator-=( const difference_type off )
    {
        return *this += -off;
    }

    // return this - integer
    DequeConstIterator operator-( const difference_type off ) const
    {
        DequeConstIterator tmp = *this;
        return tmp -= off;
    }

    // return difference of iterators
    difference_type operator-( const DequeConstIterator &right ) const
    {
        return ( static_cast< difference_type >( this->myOff - right.myOff ) );
    }

    reference operator[]( const difference_type off ) const // subscript
    {
        return *( *this + off );
    }

    // test for iterator equality
    bool operator==( const DequeConstIterator &right ) const
    {
        return this->myCont == right.myCont && this->myOff == right.myOff;
    }

    // test for iterator inequality
    bool operator!=( const DequeConstIterator &right ) const
    {
        return !( *this == right );
    }

    // test if this < right
    bool operator<( const DequeConstIterator &right ) const
    {
        return this->myOff < right.myOff;
    }

    // test if this > right
    bool operator>( const DequeConstIterator &right ) const
    {
        return right < *this;
    }

    // test if this <= right
    bool operator<=( const DequeConstIterator &right ) const
    {
        return !( right < *this );
    }

    // test if this >= right
    bool operator>=( const DequeConstIterator &right ) const
    {
        return !( *this < right );
    }

    const MyDeque *myCont; // keep a pointer to deque
    size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
    using size_type = typename MyDeque::size_type;
    using MyBase = DequeConstIterator< MyDeque >;

public:
    using value_type = typename MyDeque::value_type;
    using difference_type = typename MyDeque::difference_type;
    using pointer = typename MyDeque::pointer;
    using reference = value_type &;

    DequeIterator() // construct with null deque pointer
    {
    }

    DequeIterator( size_type off, const MyDeque *pDeque )
        : MyBase( off, pDeque ) // construct with offset off in *pDeque
    {
    }

    reference operator*() const // return designated object
    {
        return const_cast< reference >( MyBase::operator*() );
    }

    pointer operator->() const // return pointer to class object
    {
        return const_cast< pointer >( MyBase::operator->() );
        //      return &( operator*() );
    }

    DequeIterator& operator++() // preincrement
    {
        MyBase::operator++();
        return *this;
    }

    DequeIterator operator++( int ) // postincrement
    {
        DequeIterator tmp = *this;
        MyBase::operator++();
        return tmp;
    }

    DequeIterator& operator--() // predecrement
    {
        MyBase::operator--();
        return *this;
    }

    DequeIterator operator--( int ) // postdecrement
    {
        DequeIterator tmp = *this;
        MyBase::operator--();
        return tmp;
    }

    // increment by integer
    DequeIterator& operator+=( const difference_type off )
    {
        MyBase::operator+=( off );
        return *this;
    }

    // return this + integer
    DequeIterator operator+( const difference_type off ) const
    {
        DequeIterator tmp = *this;
        return tmp += off;
    }

    // decrement by integer
    DequeIterator& operator-=( const difference_type off )
    {
        MyBase::operator-=( off );
        return *this;
    }

    using MyBase::operator-; // return difference of iterators

    // return this - integer
    DequeIterator operator-( const difference_type off ) const
    {
        DequeIterator tmp = *this;
        return tmp -= off;
    }

    reference operator[]( const difference_type off ) const // subscript
    {
        return const_cast< reference >( MyBase::operator[]( off ) );
    }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using MapPtr = Ty **;

    DequeVal() // initialize values
        : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
    {
    }

    // determine block from offset
    size_type getBlock( size_type off ) const
    {
        // elements per block (a power of 2)
        size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

        return off / dequeSize % mapSize;
//      return off % ( dequeSize * mapSize ) / dequeSize;
//      return ( off / dequeSize ) & ( mapSize - 1 );
    }

    MapPtr map;        // pointer to array of pointers to blocks
    size_type mapSize; // size of map array, zero or 2^N
    size_type myOff;   // offset of initial element
    size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
    using MapPtr = Ty **;
    using ScaryVal = DequeVal< Ty >;

public:
    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    using iterator = DequeIterator< ScaryVal >;
    using const_iterator = DequeConstIterator< ScaryVal >;

    // construct empty deque
    deque()
        : myData()
    {
    }

    // destroy the deque
    ~deque()
    {
        clear();
    }

    // Assigns new contents to the container, replacing its current contents,
    // and modifying its size accordingly.
    deque& operator=( const deque &right )
    {
        if( &right != this ) // avoid self-assignment
        {
            // elements per block (a power of 2)
            size_type dequeSize = compDequeSize();

            if( myData.mySize < right.myData.mySize )
            {  // allocate memory space in the current object
                size_type newMapSize = 8;
                while( right.myData.mySize > dequeSize * newMapSize )
                    newMapSize *= 2;

                if( ( myData.myOff % dequeSize == 0 && right.myData.mySize > dequeSize * ( newMapSize - 1 ) &&
                        myData.mySize <= dequeSize * ( newMapSize - 1 ) ) ||
                    ( myData.myOff % dequeSize > 0 && myData.myOff % dequeSize + right.myData.mySize > dequeSize * newMapSize ) )
                    newMapSize *= 2;

                if( newMapSize > myData.mapSize )
                    enlargeMap( newMapSize ); // reuse the original memory space in the current object
                
                /*size_type RStartRow = getBlock(right.myData.myOff);
                size_type RlastRow = getBlock(right.myData.myOff + right.size());
                size_type startRow = getBlock(myData.myOff);
                size_type totalRow = myData.mySize / dequeSize;
                size_type count = 0;
                MapPtr p = myData.map + startRow;
                if (myData.mySize % dequeSize == 0 && myData.myOff % dequeSize != 0)
                    totalRow++;

                for (; count < totalRow && p != nullptr; p++, count++) {};

                if (count != totalRow)
                    for (size_type buffer = 0; buffer < totalRow - count; buffer++, p++)
                        *p = new value_type[dequeSize]();*/

                for (size_type n = 0; n < myData.mapSize; n++) /*not sure but why can*/
                        myData.map[n] = new value_type[dequeSize]();
                
                Ty* temp = new value_type[right.myData.mySize]();
                iterator it = begin();
                const_iterator itR = right.begin();
                /*
                size_type i = 0;

                for (; itR != right.end(); itR++, i++)
                    temp[i] = *itR;
                
                for (i = 0; it != begin() + right.size(); it++, i++)
                {
                    //cout << i << endl;
                    //cout << myData.mapSize << endl;
                    //cout << getBlock(myData.myOff + i) << " " << ((myData.myOff + i) % dequeSize) << endl;
                    *it = temp[i];
                }*/
                for (; itR != right.end(); itR++, it++)
                    *it = *itR;

                delete[] temp;
            }

            myData.mySize = right.myData.mySize;

            if( right.myData.mySize == 0 )
                myData.myOff = 0;
            else
            {  // copy data from right to the current object

                /*same as 423~425
                for (size_type i = 0; i < myData.mySize; i++)
                {
                    size_type row = ((myData.myOff + i) / dequeSize) % myData.mapSize,
                        col = (myData.myOff + i) % dequeSize;
                    size_type Rrow = ((right.myData.myOff + i) / dequeSize) % right.myData.mapSize,
                        Rcol = (right.myData.myOff + i) % dequeSize;

                    myData.map[row][col] = right.myData.map[Rrow][Rcol];
                }*/
                iterator it = begin(); const_iterator itR = right.begin();
                for (; it != end(); it++, itR++)
                    *it = *itR;
            }
        }

        return *this; // enables x = y = z, for example
    } // end function operator=

    // return iterator for beginning of mutable sequence
    iterator begin()
    {
        return iterator( myData.myOff, &myData );
    }

    // return iterator for beginning of nonmutable sequence
    const_iterator begin() const
    {
        return const_iterator( myData.myOff, &myData );
    }

    // return iterator for end of mutable sequence
    iterator end()
    {
        return iterator( myData.myOff + myData.mySize, &myData );
    }

    // return iterator for end of nonmutable sequence
    const_iterator end() const
    {
        return const_iterator( myData.myOff + myData.mySize, &myData );
    }

    // return length of sequence
    size_type size() const
    {
        return myData.mySize;
    }

    // test if sequence is empty
    bool empty() const
    {
        return myData.mySize == 0;
    }

// erase all
void clear()
{
    if( myData.mapSize > 0 )
    {
        for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
            delete[] myData.map[ i ];
        delete[] myData.map;

        myData.mapSize = 0;
        myData.mySize = 0;
        myData.myOff = 0;
        myData.map = MapPtr();
    }
}

private:

    // determine block from offset
    size_type getBlock( size_type off ) const
    {
        return myData.getBlock( off );
//      return ( ( myData.off / compDequeSize() ) & ( myData.mapSize - 1 ) );
    }

    void enlargeMap( size_type newMapSize )
    {
        size_type oldMapSize = myData.mapSize;
        myData.mapSize = newMapSize;
        value_type **newMap = new value_type * [ myData.mapSize ]();
        size_type dqSize = compDequeSize();
        size_type total = 0, startRow = myData.myOff / dqSize;
        if( myData.mySize > 0 )
        {
            /*for (size_type i = 0; i < oldMapSize; i++)
                if (myData.map[i] != nullptr)
                    total++;

            for (size_type i = startRow; i < startRow + total; i++)
                newMap[i] = new value_type[dqSize]();

            size_type count = 0;
            for (size_type i = startRow; i < oldMapSize && count < total; i++, count++)
                for (size_type j = 0; j < dqSize; j++)
                    newMap[startRow + count][j] = myData.map[i][j];

            for (size_type i = 0; count < total; i++, count++)
                for (size_type j = 0; j < dqSize; j++)
                    newMap[startRow + count][j] = myData.map[i][j];*/

            for (size_type i = startRow; i < oldMapSize; i++)
                newMap[i] = myData.map[i];

            for (size_type i = oldMapSize, j = 0; j < startRow; i++, j++) {
                if (i == myData.mapSize) {
                    i = 0;
                }
                newMap[i] = myData.map[j];
            }

            delete[] myData.map;
        }
        myData.map = newMap;
    }

    size_type compDequeSize()
    {
        return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
                sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
    }

    ScaryVal myData;
};

#endif