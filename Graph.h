//-----------------------------------------------------------------------------
// Graph.h
// Damiano Carrioli
// dcarriol
// Pa4
// Header file for the Graph type
//-----------------------------------------------------------------------------

#include "List.h"

#define INF -8 // represents infinity
#define NIL 0 // represents undefined vertex label

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

// Graph
// Exported reference type
typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// Constructor for the Graph type
Graph newGraph(int n);

// Destructor for the graph type
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);


// Manipulation procedures -----------------------------------------------------------

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);


// Other operations -----------------------------------------------------------

void printGraph(FILE* out, Graph G);


#endif