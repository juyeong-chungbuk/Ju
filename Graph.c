#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20
void insertVertex(Vertex* list); /* vertex insertion */


typedef struct Vertex { //각 그래프의 꼭지점
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;


typedef struct VertexHead { //맨위
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;


typedef struct Graph { //헤드를 나타낼 그래프?
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;


void main()
{
	
}

Graph *createGraph()/* empty graph creation */
{

	Vertex* graph = (Vertex*)malloc(sizeof(Vertex));
	graph->num = MAX_VERTEX;
	graph->link = (Vertex*)malloc(sizeof(Vertex*)*MAX_VERTEX);

	Graph* Vlist = (Graph*)malloc(sizeof(Graph)*MAX_VERTEX);
	Vlist->vlist->head = 0;
}

void destroyGraph(Graph* v) /* deallocating all allocated memory */
{
	Vertex *n, *k;
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		n = v->vlist[i];
		while (n != NULL) {
			k = n->link;

		}
	}
}

void insertVertex(Vertex* list) /* vertex insertion */
{

	if ((list->num) + 1 > MAX_VERTEX) {
		return;
	}
	list->num++;
}

void deleteVertex() /* vertex deletion */
{

}

void insertEdge(VertexHead* list,int n) /* new edge creation between two vertices */
{
	Vertex* Vlist;
	Vlist = (Vertex*)malloc(sizeof(Vertex));
	Vlist->num = n;
	Vlist->link = list->head[n];
}

void deleteEdge() /* edge removal */
{

}

void depthFS() /* depth firt search using stack */
{

}

void breadthFS(Graph* vlist, int n) /* breadth first search using queue */
{
	Vertex* v;
	int i, j;
	i = j = -1;
	vlist[n] = 0;
	while (i != j) {
		n = depthFS(&i);
		if (vlist[i]==NULL) {
			insertVertex(vlist);
		}
	}
}

void printGraph(Graph* node) /* printing graph with vertices and edges */
{
	Vertex* list;
	for (int i = 0; i < MAX_VERTEX; i++) {
		printf("정점 %d", i);
		list = node->vlist[i];
	}
}
