// list standard header

#ifndef LIST
#define LIST

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   pointer operator->() const
   {
      return &( operator*() );
//      return &( ptr->myVal );
//      return pointer_traits<pointer>::pointer_to( **this );
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator : public ListConstIterator< MyList >
{
public:
   using MyBase = ListConstIterator< MyList >;

   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   reference operator*() const
   {

      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const
   {
//      return const_cast< pointer >( MyBase::operator->() );
      return &( operator*() );
//      return &( ptr->myVal );
//      return pointer_traits<pointer>::pointer_to( **this );
   }

   ListIterator& operator++()
   {
      MyBase::operator++();
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      MyBase::operator++();
      return temp;
   }

   ListIterator& operator--()
   {
      MyBase::operator--();
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      MyBase::operator--();
      return temp;
   }
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
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

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   // empty list constructor (default constructor)
   // Constructs an empty list, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;



   }

   // List destructor
   // Destroys the list object.
   // Deallocates all the storage capacity allocated by the list.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Returns an iterator pointing to the first element in the list.
   // If the list is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list.
   // If the list is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the list is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the list is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns a reverse iterator pointing to the last element in the list
   // ( i.e., its reverse beginning ).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the last element in the list
   // ( i.e., its reverse beginning ).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the list
   // (which is considered its reverse end).
   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the list
   // (which is considered its reverse end).
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   // Returns a const_iterator pointing to the first element in the list.
   // If the list is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const
   {
      return begin();
   }

   // Returns a const_iterator pointing to the past-the-end element in the list.
   // If the list is empty, this function returns the same as list::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const
   {
      return end();
   }

   // Returns a const_reverse_iterator pointing to the last element in the list
   // (i.e., its reverse beginning).
   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   // Returns a const_reverse_iterator pointing to the theoretical element
   // preceding the first element in the list (which is considered its reverse end).
   const_reverse_iterator crend() const
   {
      return rend();
   }

   // Resizes the container so that it contains "newSize" elements.
   // If "newSize" is smaller than the current container size,
   // the content is reduced to its first "newSize" elements,
   // removing those beyond( and destroying them ).
   // If "newSize" is greater than the current container size,
   // the content is expanded by inserting at the end
   // as many elements as needed to reach a size of "newSize".
   // The new elements are initialized as 0.
   void resize( size_type newSize )
   {
      if( myData.mySize < newSize ) // pad to make larger
      {



      }
      else
      {



      }



   }

   // Returns the number of elements in the list.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list.
   // Calling this function on an empty list causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list.
   // Calling this function on an empty list causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list.
   // Calling this function on an empty list causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list.
   // Calling this function on an empty list causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // Removes all elements from the list (which are destroyed),
   // and leaving the list with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {



      }
   }

private:
   ScaryVal myData;
};

#endif // LIST
