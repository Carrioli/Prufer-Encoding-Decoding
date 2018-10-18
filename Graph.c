//-----------------------------------------------------------------------------
// Graph.c
// Damiano Carrioli
// dcarriol
// Pa4
// Graph type based on array of Lists
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"

#ifdef _DEBUG
	#include "vld.h"
#endif

// GraphObj
typedef struct GraphObj
{
	List* neighbor; // array of Lists whose ith element contains the neighbors of vertex i.
	char* color; // array of ints whose ith element is the color (white, gray, black) of vertex i.
	int* parent; // array of ints whose ith element is the parent of vertex i.
	int* distance; // array storing distances of nodes to most recent source.
	int order; // int storing number of nodes in G.
	int size; // int storing number of edges in G.
	int source; // int storing most recently used vertex as source in BFS.
} GraphObj;

// newGraph()
// constructor for the Graph type.
Graph newGraph(int n)
{
	Graph G = (Graph)malloc(sizeof(GraphObj));
	if (!G)
	{
		fprintf(stderr, "Memory allocation unsuccessful.");
		exit(1);
	}
	G->neighbor = calloc(n + 1, sizeof(List));
	if (!(G->neighbor))
	{
		fprintf(stderr, "Memory allocation unsuccessful.");
		exit(1);
	}
	G->color = calloc(n + 1, sizeof(char));
	if (!(G->color))
	{
		fprintf(stderr, "Memory allocation unsuccessful.");
		exit(1);
	}
	G->parent = calloc(n + 1, sizeof(int));
	if (!(G->parent))
	{
		fprintf(stderr, "Memory allocation unsuccessful.");
		exit(1);
	}
	G->distance = calloc(n + 1, sizeof(int));
	if (!(G->distance))
	{
		fprintf(stderr, "Memory allocation unsuccessful.");
		exit(1);
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;

	// allocate n new lists, set all fields to default values.
	for (int i = 1; i < G->order + 1; i++)
	{
		G->neighbor[i] = newList();
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	return G;
}


// freeGraph()
// destructor of the Graph type.
void freeGraph(Graph* pG)
{
	if (pG != NULL && *pG != NULL)
	{
		free((*pG)->color);
		(*pG)->color = NULL;
		free((*pG)->parent);
		(*pG)->parent = NULL;
		free((*pG)->distance);
		(*pG)->distance = NULL;
		for (int i = 1; i < (*pG)->order + 1; i++)
		{
			freeList(&(*pG)->neighbor[i]);
		}
		free((*pG)->neighbor);
		(*pG)->neighbor = NULL;

		free((*pG));
		*pG = NULL;
	}
}

// returns number of vertices
int getOrder(Graph G)
{
	return G->order;
}

// returns number of edges
int getSize(Graph G)
{
	return G->size;
}

// returns most recent source used in BFS
int getSource(Graph G)
{
	return G->source;
}

// returns parent of vertex u
int getParent(Graph G, int u)
{
	if (u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Graph error: cannot get parent of non existing vertex.\n");
		exit(EXIT_FAILURE);
	}
	return (G->parent[u]);
}

// returns distance from most recent source to vertex u
int getDist(Graph G, int u)
{
	if (u < 1 || u > getOrder(G))
	{
		fprintf(stderr, "Graph error: cannot get distance from most recent source to specified vertex.\n");
		exit(EXIT_FAILURE);
	}
	return (G->distance[u]);
}


// returns shortest path from source of G to vertex u.
void getPath(List L, Graph G, int u)
{
	if (getSource(G) == NIL)
	{
		fprintf(stderr, "Graph error: cannot call getPath() before BFS().\n");
		exit(EXIT_FAILURE);
	}
	if (G->source == u)
	{
		append(L, u);
	}
	else if (G->parent[u] == NIL)
	{
		append(L, NIL);
	}
	else
	{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}




// Deletes all edges in G
void makeNull(Graph G) 
{
	for (int i = 1; i < G->order + 1; i++)
	{
		clear(G->neighbor[i]);
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = NIL;
	G->size = 0;
}

// add edge in between vertex u and v
void addEdge(Graph G, int u, int v)
{
	addArc(G, u, v);
	addArc(G, v, u);
}


// insert arc in adjacency list of u in increasing order
void addArc(Graph G, int u, int v)
{
	int end_while = 0;

	//if list is empty: prepend
	if (length(G->neighbor[u]) == 0) 
	{
		prepend(G->neighbor[u], v);
	}
	// if element to be added is greater than last element: append
	else if (back(G->neighbor[u]) < v)
	{
		append(G->neighbor[u], v);
	}
	// else find its position in the list
	else
	{
		moveFront(G->neighbor[u]);
		while (!end_while)
		{
			if (get(G->neighbor[u]) > v)
			{
				insertBefore(G->neighbor[u], v);
				end_while = 1;
			}
			moveNext(G->neighbor[u]);
		}
	}

}

// Breadth First Search
void BFS(Graph G, int s)
{
	int u;
	int v;
	for (int i = 1; i < G->order + 1; i++)
	{
		if (i == s) continue;
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = 'g';
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List Q = newList();
	append(Q, s);
	while (length(Q) > 0)
	{
		u = front(Q);
		deleteFront(Q);
		moveFront(G->neighbor[u]);
		while (index(G->neighbor[u]) != -1)
		{
			v = get(G->neighbor[u]);
			if (G->color[v] == 'w')
			{
				G->color[v] = 'g';
				G->distance[v] = (G->distance[u] + 1);
				G->parent[v] = u;
				append(Q, v);
			}
			G->color[u] = 'b';
			moveNext(G->neighbor[u]);
		}
	}
	freeList(&Q);

}

// prints out graph to specified file
void printGraph(FILE * out, Graph G)
{
	for (int i = 1; i < G->order + 1; i++)
	{
		fprintf(out, "%d: ", i);
		printList(out, G->neighbor[i]);
	}
}

