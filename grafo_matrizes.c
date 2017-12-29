#include <stdio.h>
#include <stdlib.h>
#define MAX 10
typedef struct adj_list
{
	int item;
	struct adj_list *next;
}adj_list;

typedef struct graph
{
	int vertices[MAX][MAX];
	short visited[MAX];
}graph;
// necessario para BFS
typedef struct queue
{
	adj_list *head;
}queue;

queue* create_queue()
{
	queue *new_queue = (queue*) malloc(sizeof(queue));
	new_queue->head = NULL;
	return new_queue;	
} 

void enqueue(queue *q, int item)
{

	adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
	new_adj_list->item = item;
	if(q->head == NULL)
	{
		q->head = new_adj_list;
		new_adj_list->next = NULL;
	}
	else
	{
	
		adj_list *current = q->head;
		while(current->next != NULL)current = current->next;
		current->next = new_adj_list;
		new_adj_list->next = NULL;
	}
}

adj_list* dequeue(queue *q)
{
	if(q->head == NULL)return NULL;
	adj_list *aux = q->head;
	q->head = q->head->next;
	aux->next = NULL;
	return aux;
}

graph* create_graph()
{
	graph *new_graph = (graph*) malloc(sizeof(graph));
	int i, j;
	for (i = 0; i < MAX; ++i)
	{ 
		for (j = 0; j < MAX; ++j)
		{
			new_graph->vertices[i][j] = 0;
		}
		new_graph->visited[i] = 0;
	}
	return new_graph;
}

adj_list* create_adj_list(int item)
{
	adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
	new_adj_list->item = item;
	new_adj_list->next = NULL;
	return new_adj_list;
}
//Undirected
void add_edge(graph *graph, int vertex1, int vertex2)
{
	graph->vertices[vertex1][vertex2] = 1;
	graph->vertices[vertex2][vertex1] = 1;
}
//DFS

void busca_profundidade(graph *graph, int source)
{
	int i;
	graph->visited[source] = 1;
	printf("%d\n", source);
	for (i = 0; i < MAX; ++i)
	{
		if (graph->vertices[source][i] && !graph->visited[i])
		{
			busca_profundidade(graph, i);
		}
	}
}

//BFS
void busca_largura(graph *graph, int source)
{
	queue *queue = create_queue();
	int i, aux;//necessario pois meu dequeue retorna o node inteiro
	adj_list *dequeued = NULL;
	graph->visited[source] = 1;
	printf("%d\n", source);
	enqueue(queue, source);
	while(queue->head != NULL)
	{
		dequeued = dequeue(queue);
		aux = dequeued->item;
		free(dequeued);
		dequeued = NULL;
		for( i=0; i < MAX; ++i)
		{
			if(!graph->visited[i] && graph->vertices[aux][i])
			{
				printf("%d\n", i);
				graph->visited[i] = 1;
				enqueue(queue, i);
			}
		} 
	}
}

int main()
{
	graph *new_graph;// undirected graph
	new_graph = create_graph();

	add_edge(new_graph, 6, 4);
	add_edge(new_graph, 6, 9);
	add_edge(new_graph, 9, 1);
	add_edge(new_graph, 9, 2);
	add_edge(new_graph, 1, 5);
	add_edge(new_graph, 1, 3);

	//busca_profundidade(new_graph, 6);
	busca_largura(new_graph, 6);
	return 0;
}