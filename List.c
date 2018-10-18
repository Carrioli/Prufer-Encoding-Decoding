//-----------------------------------------------------------------------------
// List.c
// Damiano Carrioli
// dcarriol
// Pa4
// dictionary type based on doubly linked list data structure
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// NodeObj
typedef struct NodeObj
{
	int item;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// Node
typedef NodeObj* Node;

// ListObj
typedef struct ListObj
{
	Node front;		// reference to first Node in List
	Node back;		// reference to last Node in List
	int numItems;
	int cursor;
} ListObj;

// private helper function
Node findNode(List L, int cursor);

// newNode()
// constructor of the Node type
Node newNode(int a)
{
	Node N = (Node)malloc(sizeof(NodeObj));		// Allocate space on the heap for Node object
	assert(N != NULL);							// Check that allocation is successfull

	N->item = a;

	N->next = NULL;
	N->prev = NULL;
	return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN)
{
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// delete a single node N
void deleteNode(List L, Node N)
{
	Node M; // previous of N
	Node K; // next of N

	if (N == L->front) {
		// first node of L (can be also the last one)
		K = N->next;
		L->front = K;
		if (K != NULL)
			K->prev = NULL;
		else // it is also the last one
			L->back = NULL;
	}
	else if (N == L->back) {
		// last node of D (cannot be also the first one)
		M = N->prev;
		M->next = NULL;
		L->back = M;
	}
	else {
		// node in the middle
		K = N->next;
		M = N->prev;
		M->next = K;
		K->prev = M;
	}

	freeNode(&N);
	L->numItems--;
}

// Given the cursor, this function returns the element associated with it.
Node findNode(List L, int cursor)
{
	Node N;
	N = L->front;
	if (cursor == -1) return NULL;
	else
	{
		for (int i = 0; i < cursor; i++)
		{
			N = N->next;
		}
		return N;
	}
}

// newList()
// constructor for the List type.
List newList(void)
{
	List S = (List)malloc(sizeof(ListObj));
	assert(S != NULL);
	S->front = NULL;
	S->back = NULL;
	S->numItems = 0;
	S->cursor = -1;
	return S;
}

// freeList()
// destructor for the List type.
void freeList(List* pL)
{
	Node N;
	if (pL != NULL && *pL != NULL)
	{
		while ((*pL)->numItems != 0)
		{
			N = findNode(*pL, 0); // Always delete first element (not time consuming) until list is empty.
			deleteNode(*pL, N);
		}
	}
	free(*pL);
	*pL = NULL;
}

int length(List L)
{
	return L->numItems;
}

int index(List L)
{
	return L->cursor;
}

int front(List L)
{
	if (L->numItems == 0)
	{
		fprintf(stderr, "List error : cannot return front element when list is empty.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		return L->front->item;
	}
}

int back(List L)
{
	if (L->numItems == 0)
	{
		fprintf(stderr, "List error : cannot return back element when list is empty.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		return L->back->item;
	}
}

int get(List L)
{
	Node N;
	if (L->numItems == 0)
	{
		fprintf(stderr, "List error: cannot return cursor element when list is empty.\n");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor < 0)
	{
		fprintf(stderr, "List error: cannot return element when when cursor is undefined.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		N = findNode(L, L->cursor);
	}
	return N->item;
}

int equals(List A, List B)
{
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL)
	{
		fprintf(stderr, "List Error: calling equals(*,*) on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	eq = (A->numItems == B->numItems);
	N = A->front;
	M = B->front;
	while (eq && N != NULL)
	{
		eq = (N->item == M->item);
		N = N->next;
		M = M->next;
	}
	return eq;
}

void clear(List L)
{
	Node N;
	while (L->numItems != 0)
	{
		N = findNode(L, 0); // Always delete first element (not time consuming) until list is empty.
		deleteNode(L, N);
	}
	L->numItems = 0;
	L->cursor = -1;
}

void moveFront(List L)
{
	if (L->numItems > 0)
	{
		L->cursor = 0;
	}
}

void moveBack(List L)
{
	if (L->numItems > 0)
	{
		L->cursor = L->numItems - 1;
	}
}

void movePrev(List L)
{
	if (L->cursor == 0)
	{
		L->cursor = -1;
	}
	else if (L->cursor > 0)
	{
		L->cursor -= 1;
	}
}

void moveNext(List L)
{
	if (L->cursor == L->numItems - 1)
	{
		L->cursor = -1;
	}
	else if (L->cursor < L->numItems - 1) {
		L->cursor += 1;
	}
}

void prepend(List L, int data)
{
	if (L->numItems == 0)
	{
		L->front = newNode(data);
		L->back = L->front;
	}
	else
	{
		Node N = newNode(data);
		N->next = L->front;
		L->front = N;
		N = N->next;
		N->prev = L->front;
	}
	L->numItems++;
	if (L->cursor >= 0) {
		L->cursor += 1;
	}
}

void append(List L, int data)
{
	if (L->numItems == 0)
	{
		L->front = newNode(data);
		L->back = L->front;
	}
	else
	{
		Node N = newNode(data);
		L->back->next = N;
		N->prev = L->back;
		L->back = L->back->next;
	}
	L->numItems++;
}

void insertBefore(List L, int data)
{
	if (L->numItems <= 0)
	{
		fprintf(stderr, "List error: cannot insert element before cursor when list is empty.");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor < 0)
	{
		fprintf(stderr, "List error: cannot insert element when cursor is undefined.");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor == 0)
	{
		prepend(L, data);
	}
	else
	{
		Node N = newNode(data);
		Node M = L->front;
		Node O = L->front;
		for (int i = 0; i < L->cursor - 1; i++) // M is a reference to the left node to be split
		{
			M = M->next;
		}
		for (int i = 0; i < L->cursor; i++) //O is a reference to the right node to be split
		{
			O = O->next;
		}
		M->next = N;
		N->prev = M;
		N->next = O;
		O->prev = N;
		L->cursor += 1;
		L->numItems++;
	}
}

void insertAfter(List L, int data)
{
	if (L->numItems <= 0)
	{
		fprintf(stderr, "List error: cannot insert element before cursor when list is empty.");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor < 0)
	{
		fprintf(stderr, "List error: cannot insert element when cursor is undefined.");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor == L->numItems - 1)
	{
		append(L, data);
	}
	else {
		Node N = newNode(data);
		Node M = L->front;
		Node O = L->front;
		for (int i = 0; i < L->cursor; i++) // M is a reference to the right node to be split
		{
			M = M->next;
		}
		for (int i = 0; i < L->cursor + 1; i++) //O is a reference to the left node to be split
		{
			O = O->next;
		}
		M->next = N;
		N->prev = M;
		N->next = O;
		O->prev = N;
		L->numItems++;
	}
}

void deleteFront(List L)
{
	if (L->numItems <= 0)
	{
		fprintf(stderr, "List error: cannot delete first element when list is empty.");
		exit(EXIT_FAILURE);
	}
	else
	{
		Node N = findNode(L, 0);
		deleteNode(L, N);

	}

}

void deleteBack(List L)
{
	if (L->numItems <= 0)
	{
		fprintf(stderr, "List error: cannot delete last element when list is empty.");
		exit(EXIT_FAILURE);
	}
	else
	{
		Node N = findNode(L, L->numItems - 1);
		deleteNode(L, N);

	}

}

void delete(List L)
{
	if (L->numItems <= 0)
	{
		fprintf(stderr, "List error: cannot delete index element when list is empty.");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor < 0)
	{
		fprintf(stderr, "List error: cannot delete index element when index is undefined");
		exit(EXIT_FAILURE);
	}
	else if (L->cursor == 0) // Special case, first element.
	{
		deleteFront(L);
	}
	else if (L->cursor == L->numItems - 1) // Special case, last element.
	{
		deleteBack(L);
	}
	else
	{
		Node N = findNode(L, L->cursor);
		deleteNode(L, N);
	}
	L->cursor = -1;

}

void printList(FILE* out, List L)
{
	Node N;
	if (L == NULL)
	{
		fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for (N = L->front; N != NULL; N = N->next)
	{
		if (N->next == NULL)
		{
			fprintf(out, "%d", N->item);
		}
		else
		{
			fprintf(out, "%d ", N->item);
		}
	}
	fprintf(out, "\n");
}

List copyList(List L)
{
	List C = newList();
	Node N = L->front;
	while (N != NULL)
	{
		append(C, N->item);
		N = N->next;
	}
	return C;
}


