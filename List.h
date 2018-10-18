//-----------------------------------------------------------------------------
// List.h
// Damiano Carrioli
// dcarriol
// Pa4
// Header file for the List type
//-----------------------------------------------------------------------------


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// List
// Exported reference type
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------


// newList()
// constructor for the List type.
List newList(void);

// freeList()
// destructor for the List type.
void freeList(List* pL);


// Access functions -----------------------------------------------------------


// Returns the number of elements in this List.
// Pre: none.
int length(List L);

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L);

// Returns front element. Pre: length()>0.
int front(List L);

// Returns back element. Pre: length()>0.
int back(List L);

// Returns cursor element. Pre: length()>0, index()>=0.
int get(List L);

// Returns true if this List and L are the same integer sequence.
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------


// Resets this List to its original empty state.
void clear(List L);

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L);

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one step toward front of this List,
// if cursor is defined and at front, cursor becomes undefined,
// if cursor is undefined does nothing.
void movePrev(List L);

// If cursor is defined and not at back, moves cursor one step toward back of this List,
// if cursor is defined and at back, cursor becomes undefined,
// if cursor is undefined does nothing.
void moveNext(List L);

// Insert new element into this List.
// If List is non-empty, insertion takes place before front element.
void prepend(List L, int data);

// Insert new element into this List.
// If List is non-empty, insertion takes place after back element.
void append(List L, int data);

// Insert new element before cursor.
// Pre: length()>0, index()>=0.
void insertBefore(List L, int data);

// Inserts new element after cursor.
// Pre: length()>0, index()>=0.
void insertAfter(List L, int data);

// Deletes the front element. Pre: length()>0.
void deleteFront(List L);

// Deletes the back element. Pre: length()>0.
void deleteBack(List L);

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0.
void delete(List L);


// Other operations -----------------------------------------------------------


// pre: none
// prints a text representation of L to the file pointed to by out.
void printList(FILE* out, List L);

// Returns a new List representing the same integer sequence as List L.
// The cursor in the new list is undefined, regardless of the
// state of the cursor in List L. List L is unchanged.
List copyList(List L);



#endif