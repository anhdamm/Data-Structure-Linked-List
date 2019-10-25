//--------------------------------------------------------------------
//
//  Laboratory 5                                          ListLinked.h
//
//  Class declaration for the linked implementation of the List ADT
//
//--------------------------------------------------------------------

#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class List {
public:
    List(int ignored = 0);
    List(const List& other);
    List& operator=(const List& other);
    ~List();
	
    void insert(const DataType& newDataItem) throw (logic_error);
    void remove() throw (logic_error);
    void replace(const DataType& newDataItem) throw (logic_error);
    void clear();
	
    bool isEmpty() const;
    bool isFull() const;
	
    void gotoBeginning() throw (logic_error);
    void gotoEnd() throw (logic_error);
    bool gotoNext() throw (logic_error);
    bool gotoPrior() throw (logic_error);
	
    DataType getCursor() const throw (logic_error);
	
    // Programming exercise 2
    void moveToBeginning () throw (logic_error);
	
    // Programming exercise 3
    void insertBefore(const DataType& newDataItem) throw (logic_error);
    
    void showStructure() const;
	
private:
    class ListNode {
	public:
		ListNode(const DataType& nodeData, ListNode* nextPtr);
		
		DataType dataItem;
		ListNode* next;
    };
	
    ListNode* head;
    ListNode* cursor;
};

/*Constructor
 Pre: none.
 Post: Creates an initialized ListNode.
 */
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}

/*Constructor
 Pre: none
 Post: Constructor. Creates an empty list.
 */
template <typename DataType>
List<DataType>::List(int ignored)
: head(0), cursor(0)
{
}


/*Constructor
 Pre: none
 Post: Copy constructor. Initializes the list to be equivalent to the source List object parameter.
 */
template <typename DataType>
List<DataType>::List ( const List& other )
:head(0) , cursor(0)
{
    operator = (other);
}


/*Constructor
 Pre: none
 Post: Sets the list to be equivalent to the source object parameter and returns a reference to the object.
 */
template <typename DataType>
List<DataType>& List<DataType>:: operator= ( const List &other )
{
        if( this != &other ) {
            
            clear();
            ListNode *otherPtr = other.head;
            ListNode holdCursor = 0;
            while ( otherPtr != 0 )
            {
                insert(otherPtr->dataItem);
                if(otherPtr == other.cursor)
                {
                    holdCursor = cursor;
                }
                otherPtr = otherPtr->next;
            }
            cursor = holdCursor;
        }
        return *this;
}



/*Destructor
 Pre: none
 Post: frees the memory used to store the list.
 */
template <typename DataType>
List<DataType>::~List()
{
    clear();
}
    


/*Constructor
 Pre: List is not full.
 Post: Inserts newDataItem to the list.
 */
template <typename DataType>
void List<DataType>::insert(const DataType &newDataItem) throw(logic_error)
{
    if (isFull())
    {
        throw logic_error ("List is full.");
    }
    else if (isEmpty())
    {
        head = new ListNode(newDataItem, 0);
        cursor = head;
    }
    else
    {
        ListNode* tempNode = cursor;
        cursor = new ListNode(newDataItem, tempNode->next);
        tempNode->next = cursor;
    }
}



/*Constructor
 Pre: List is not empty
 Post: Removes the data item marked by the cursor from the list.
 */
template <typename DataType>
void List<DataType>::remove() throw(logic_error)
{
    ListNode* Node = cursor;
    if(isEmpty())
    {
        throw logic_error("List is empty. Please add elements to the list.");
    }
    else
    {
        if((cursor == head) && (cursor->next == NULL))
        {
            cursor = NULL;
            head = NULL;
        }
        else if(cursor == head)
        {
            gotoNext();
            head = cursor;
        }
        else
        {
            gotoPrior();
            cursor->next = Node->next;
            if(Node->next != NULL)
            {
                gotoNext();
            }
            else
            {
                gotoBeginning();
            }
        }
        delete Node;
    }
}



/*replace
 Pre: List is not empty
 Post: Replaces the data item marked by the cursor with newDataItem.
 */
template <typename DataType>
void List<DataType>::replace(const DataType &newDataItem) throw(logic_error)
{
    if(isEmpty())
    {
        throw logic_error("List is empty. Please add elements to the list.");
    }
    else
    {
        cursor->dataItem = newDataItem;
    }
}



/*Clear
 Pre: none
 Post: Removes all the data items in the list.
 */
template <typename DataType>
void List<DataType>::clear()
{
    ListNode* ptr = head;
    gotoBeginning();
    while(head != NULL)
    {
        head = ptr->next;
        delete ptr;
        ptr = head;
    }
    cursor = 0;
}



/*IsEmpty
 Pre: none
 Post: Returns true if the list is empty. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::isEmpty() const
{
    return (head == 0);
}


/*Constructor
 Pre: none
 Post: Returns true if the list is full. Otherwise,returns false.
 */
template <typename DataType>
bool List<DataType>::isFull() const
{
    return false;
}


/*Constructor
 Pre: List is not empty.
 Post: moves the cursor to the data item at the beginning of the list.
 */
template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
    if(isEmpty())
    {
        throw logic_error("The list is empty. Please add elements to the list");
    }
    else
    {
        cursor = head;
    }
}


/*GotoEnd.
 Pre: List is not empty.
 Post: moves the cursor to the data item at the end of the list.
 */
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
    if(isEmpty())
    {
        throw logic_error("The list is empty. Please add elements to the list");
    }
    else
    {
        while(cursor->next != NULL)
        {
            cursor = cursor->next;
        }
    }
}



/*gotoNext
 Pre: List is not empty.
 Post: moves the cursor to the next data item in the list and returns true. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
    if(isEmpty())
    {
        throw logic_error ("The list is empty. Please add elements to the list");
    }
    
    else if(cursor->next == NULL)
    {
        return false;
    }
    else
    {
        cursor = cursor->next;
        return true;
    }
}


/*Constructor
 Pre: List is not empty.
 Post: moves the cursor to the preceding t data item in the list and returns true. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
    bool result;
    if(isEmpty())
    {
        throw logic_error ("The list is empty. Please add elements to the list");
    }
    
    else if(cursor == head)
    {
        result = false;
    }
    else
    {
        ListNode* temp = cursor;
        for(cursor = head; cursor->next != temp; cursor = cursor->next)
        {
            result= true;
        }
    }
    return result;
}



/*Constructor
 Pre: List is not empty.
 Post: Returns the value of the data item marked by the cursor.
 */
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
    if(isEmpty())
    {
        throw logic_error ("The list is empty. Cannot return the item.");

    }
    else
    {
        return cursor->dataItem;
    }
}

template <typename DataType>
void List<DataType>::showStructure() const
    
    // Outputs the items in a list. If the list is empty, outputs
    // "Empty list". This operation is intended for testing and
    // debugging purposes only.
{
    if (isEmpty() )
    {
        cout << "Empty list" << endl;
    }
    else
    {
        for (ListNode* temp = head; temp != 0; temp = temp->next) {
            if (temp == cursor) {
                cout << "[";
            }
                        
        // Assumes that dataItem can be printed via << because
        // is is either primitive or operator<< is overloaded.
            cout << temp->dataItem;
                        
            if (temp == cursor) {
                cout << "]";
            }
                cout << " ";
        }
    cout << endl;
    }
}
#endif

