//---------------------------------------------------------------------------------
// Main file for Prufer coding
// input: Prufer code terminated by 0
// output: adjacency matrix representing the tree associated with the Prufer code
//---------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"



Graph prufer(List P, List L)
{
	int L_length = length(L);
	Graph G = newGraph(L_length);


	moveFront(L);

	int x;
	int y;
	while (index(L) != -1)
	{
		moveFront(P);
		x = get(L);
		while (index(P) != -1)
		{
			y = get(P);
			if (x == y) break;
			moveNext(P);
		}
		if (index(P) == -1)	// no such element is in P
		{
			moveFront(P);
			y = get(P);
			x = get(L);
			addEdge(G, x, y);
			delete(P);
			delete(L);
			moveFront(L);
		}
		else
		{
			moveNext(L);
		}
		if (length(L) == 2) break;
	}
	moveFront(L);
	x = get(L);
	moveNext(L);
	y = get(L);
	addEdge(G, x, y);

	return G;
}


int main(int argc, char* argv[])
{
	FILE *in, *out;

	// check command line for correct number of arguments (two command line arguments plus the program itself)
	if (argc != 3)
	{
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open input file for reading 
	if ((in = fopen(argv[1], "r")) == NULL)
	{
		printf("Unable to read from file %s.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// open output file for writing
	if ((out = fopen(argv[2], "w")) == NULL)
	{
		printf("Unable to write to file %s.\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	

	int x;
	// list that keeps track of Prufer code
	List P = newList();

	while (fscanf(in, "%d", &x) == 1)
	{
		if (x == 0) break;
		append(P, x);
	}


	printf("Prufer code: ");
	printList(stdout, P);

	int P_length = length(P);
	int L_length = P_length + 2;

	// additional list to build edges
	List L = newList();
	for (int i = L_length; i > 0; i--) 
	{
		prepend(L, i);
	}

	Graph G = prufer(P, L);

	printGraph(stdout, G);

	// free data structures
	freeGraph(&G);
	freeList(&P);
	freeList(&L);

	// close input file
	fclose(in);

	// close output file
	fclose(out);


	return 0;
}

 