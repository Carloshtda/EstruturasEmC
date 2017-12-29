#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	void *item;
	struct node *next;
}node;
//inicializa uma lista vazia
node* create_list()
{
	return NULL;
}
//returna 1 se a lista ta vazia e 0 se não.
int is_empty(node* head)
{
	return(head == NULL);
}
//adciona um node no começo da lista
node* add(node* head, void* item)
{
	node* new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = head;
	return new_node;
}
//adciona um node no final da lista
node* add_end(node* head, void* item)
{
	if(head == NULL)
	{
		node* new_node = (node*) malloc(sizeof(node));
		new_node->item = item;
		new_node->next = head;
		return new_node;
	}
	node* aux = head;
	while(head->next != NULL)
	{
		head = head->next;
	}
	node* new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = head->next;
	head->next = new_node;
	return aux;
}
//imprime uma lista q contem inteiros
void print_list_int(node* head)
{
	node* aux = head;
	if (aux == NULL)printf("Lista vazia\n");
	while(aux != NULL)
	{
		printf("%d ", *((int *)aux->item));
		aux=aux->next;
	}
	printf("\n");
}
node* remove_int(node* head, int item)
{
	node *previous = NULL;
	node *current = head; 
	while(current != NULL && *((int *)current->item) != item)
	{
		previous = current;
		current= current->next;
	}
	if(current == NULL)
	{
		return head;
	}
	if(previous == NULL)
	{
		head = current->next;
	}
	else
	{
		previous->next = current->next;
	}
	free(current);
	return head;
}
int main()
{
	int i, *p;
	node *lista;
	lista = create_list();
	for (i = 0; i < 5; ++i)
	{
		p = malloc(sizeof(int));
		*p = i;
		lista = add_end(lista, p);
	}	
	print_list_int(lista);//nesse caso só está imprimindo 5 que é o valor de i
	lista = remove_int(lista, 3);
	print_list_int(lista);
	return 0;
}