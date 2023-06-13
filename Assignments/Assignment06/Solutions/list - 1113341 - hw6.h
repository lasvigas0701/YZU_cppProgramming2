// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
    ListNode *next;  // successor node, or first element if head
    ListNode *prev;  // predecessor node, or last element if head
    ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
    using node = ListNode< Ty >;
    using nodePtr = node *;

    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    ListVal() // initialize data
        : myHead(),
        mySize( 0 )
    {
    }

    nodePtr myHead; // pointer to head node
    size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
    using node = ListNode< Ty >;
    using nodePtr = node *;
    using ScaryVal = ListVal< Ty >;

public:
    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    using iterator = node *;
    using const_iterator = const node *;

    // empty container constructor (default constructor)
    // Constructs an empty container, with no elements.
    list()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;
    }

    // fill constructor
    // Constructs a container with "count" elements.
    // Each element is initialized as 0.
    list( size_type count ) // construct list from count * Ty()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;
        myData.mySize = count;
        nodePtr temp = myData.myHead;
        for (; count--; )
        {
            temp->next = new node;
            temp->next->myVal = Ty();
            temp->next->prev = temp;
            temp->next->next = myData.myHead;
            temp = temp->next;
        }
        myData.myHead->prev = temp;
    
        /*myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;
        
        for (size_type i = 0; i < count; i++)
        {
            nodePtr temp = new node;
            temp->myVal = Ty();
            temp->next = myData.myHead->next;
            temp->prev = myData.myHead;
            
            myData.myHead->next->prev = temp;
            myData.myHead->next = temp;
            myData.mySize++;
        }*/
    }

    // copy constructor
    // Constructs a container with a copy of each of the elements in "right",
    // in the same order.
    list( const list &right )
        : myData()
    {
        myData.mySize = right.size();
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        nodePtr temp = myData.myHead; const_iterator rightTemp = right.begin();
        for (size_type i = 0; i < size(); i++)
        {
            temp->next = new node;
            temp->next->myVal = rightTemp->myVal;
            temp->next->prev = temp;
            temp = temp->next; rightTemp = rightTemp->next;
        }
        temp->next = myData.myHead;
        myData.myHead->prev = temp;
    }

    // List destructor
    // Destroys the container object.
    // Deallocates all the storage capacity allocated by the list container.
    ~list()
    {
        clear();
        delete myData.myHead;
    }

    // Assigns new contents to the container, replacing its current contents,
    // and modifying its size accordingly.
    // Copies all the elements from "right" into the container
    // (with "right" preserving its contents).
    list& operator=( const list &right )
    {
        if( this != &right )
        {
            nodePtr temp = myData.myHead;/*myData.myHead->next*/
            nodePtr rightTemp = right.myData.myHead;
            if (myData.mySize < right.myData.mySize)
            {
                /*cout << "case1\n";*/
                size_type count = myData.mySize;

                for (size_type i = 0; i < size(); i++)
                {
                    temp->next->myVal = rightTemp->next->myVal;
                    temp = temp->next; rightTemp = rightTemp->next;
                }
                for (size_type i = size(); i < right.size(); i++)
                {
                    temp->next = new node;
                    temp->next->myVal = rightTemp->next->myVal;
                    temp->next->prev = temp;
                    temp = temp->next; rightTemp = rightTemp->next;
                }
            }
            else if (size() > right.size())
            {
                /*cout << "case2\n";*/
                for (size_type i = 0; i < right.size(); i++)
                {
                    temp->next->myVal = rightTemp->next->myVal;
                    temp = temp->next; rightTemp = rightTemp->next;
                }

                /*delete the rest of nodes in *this list*/
                nodePtr del = temp->next, buf = del->next;
                do {
                    delete del;
                    del = buf;
                    buf = buf->next;
                } while (del != myData.myHead);
            }
            else
            {
                /*cout << "case3\n";*/
                for (size_type i = 0; i < size(); i++)
                {
                    temp->next->myVal = rightTemp->next->myVal;
                    temp = temp->next; rightTemp = rightTemp->next;
                }
            }

            temp->next = myData.myHead;
            myData.myHead->prev = temp;
            myData.mySize = right.size();
        }

        return *this;
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    iterator begin()
    {
        return iterator( myData.myHead->next );
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    const_iterator begin() const
    {
        return const_iterator( myData.myHead->next );
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    iterator end()
    {
        return iterator( myData.myHead );
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    const_iterator end() const
    {
        return const_iterator( myData.myHead );
    }

    // Returns the number of elements in the list container.
    size_type size() const
    {
        return myData.mySize;
    }

    // Returns whether the list container is empty (i.e. whether its size is 0).
    bool empty() const
    {
        return myData.mySize == 0;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference front()
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference front() const
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference back()
    {
        return myData.myHead->prev->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference back() const
    {
        return myData.myHead->prev->myVal;
    }

    // The container is extended by inserting a new element
    // before the element at the specified position.
    // This effectively increases the list size by the amount of elements inserted.
    // Returns an iterator that points to the newly inserted element.
    iterator insert( const_iterator where, const Ty &val ) // insert val at where
    {
        /*iterator temp = where;
        temp->prev = new node;
        temp->prev->myVal = val;
        temp->prev->next = where; temp->prev->prev = temp->prev;
        where->prev = temp->prev;*/
        
        nodePtr here = (iterator)where; 
        nodePtr newVal = new node;
        newVal->myVal = val; 
        newVal->prev = here->prev; here->prev->next = newVal; 
        here->prev = newVal; newVal->next = here; /*the next one of newVal is here*/

        /*nodePtr add = new node;
        add->myVal = val;
        where->prev->next = add; add->prev = where->prev;
        where->prev = add; add->next = where;*/
        
        myData.mySize++;
        return newVal;
    }

    // Removes from the list container the element at the specified position.
    // This effectively reduces the container size one, which is destroyed.
    // Returns an iterator pointing to the element that followed the element erased.
    // This is the container end if the operation erased the last element in the sequence.
    iterator erase( const_iterator where )
    {
        /*cout << "wherenext: " << where->next << endl;
        cout << where << endl;*/
        iterator re = where->next;
        /*cout << "wn: " << where->next << endl;*/
        if (where != myData.myHead)
        {
            where->prev->next = where->next;
            where->next->prev = where->prev;
            delete where;
        }
        /*cout << where->next << endl;
        cout << re << endl;*/
        myData.mySize--;
        return re;
    }

    // Removes all elements from the list container (which are destroyed),
    // and leaving the container with a size of 0.
    void clear() // erase all
    {
        if( myData.mySize != 0 ) // the list is not empty
        {
            iterator i = begin(), buf = i->next;
            for (; i != myData.myHead; i = buf, buf = buf->next)
                delete i;

            myData.mySize = 0;
        }
    }

private:
    ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    if (left.size() != right.size())
        return false;

    typename list<Ty>::nodePtr tempL = left.begin(), tempR = left.begin();
    /*tempL = left.myData.myHead->next*/
    for (size_t i = 0; i < left.size(); i++)
    {
        if (tempL->myVal != tempR->myVal)
            return false;
        tempL = tempL->next; tempR = tempR->next;
    }
    
    return true;
}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
    return !( left == right );
}

#endif // LIST