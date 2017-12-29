#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct _deque deque_t;
typedef struct _node  node_t;
struct _node
{
	  node_t *prev;
  	node_t *next;
  	int    value;
};

struct _deque 
{
  	node_t *front;
  	node_t  *rear;
  	int      size;
};

//Cria um node que guarda os valores que sãoo enfileirados no deque
node_t* node_new(int value)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->prev = NULL; 
    new_node->next = NULL;
    return new_node;
}

//Cria um deque dinamicamente e retorna seu endere�o de memoria
deque_t* construct()
{
  deque_t* new_node = (deque_t*)malloc(sizeof(deque_t));
  new_node->front = NULL;
  new_node->rear = NULL;
  new_node->size = 0;
  return new_node;
}
//Libera a memoria do conte�do e do pr�prio deque
void destruct(deque_t *deque)
{
  node_t* aux;
  while(deque->front != NULL)
  {
    aux = deque->front;
    deque->front = deque->front->next;
    free(aux);
  }
  free(deque);
}
//Retorna o tamanho do deque
int size (deque_t *deque)
{
  return deque->size;
}
//Retorna 1 se o deque esta vazio, caso contrario, retora 0
int empty (deque_t *deque)
{
  return (deque->size == 0);
}

//Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int front (deque_t *deque)
{
  if(deque->front == NULL)
  {
    return INT_MIN;
  }
  return deque->front->value;
}
//Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int rear(deque_t *deque)
{
  if(deque->rear == NULL)
  {
    return INT_MIN;
  }
  return deque->rear->value;
}

//Cria um node que guarda um valor e o adiciona ao fim do deque
void enqueue_rear(deque_t *deque, int value)
{
  node_t* novo_node = node_new(value);
  if(deque->size == 0)
  {
    deque->front = novo_node;
    deque->rear= novo_node;
    deque->size++;
  }
  else
  {
    novo_node->prev = deque->rear;
    novo_node->next = deque->rear->next;
    deque->rear->next = novo_node;
    deque->rear = novo_node;
    deque->size++;

  }
}
//Cria um node que guarda um valor e o adiciona ao inicio do deque
void enqueue_front(deque_t *deque, int value)
{
  node_t* novo_node = node_new(value);
  if(deque->size == 0)
  {
    deque->front = novo_node;
    deque->rear= novo_node;
    deque->size++;
  }
  else
  {
    novo_node->next = deque->front;
    novo_node->prev = deque->front->prev;
    deque->front->prev = novo_node;
    deque->front = novo_node;
    deque->size++;

  }
}
//Retira o valor do final caso nao esteja vazia
node_t* dequeue_rear (deque_t *deque)
{
  if(deque->size == 0)
  {
    return NULL;
  }
  if(deque->size == 1)
  {
    node_t* aux = deque->rear;
    deque->rear = NULL;
    deque->front = NULL;
    deque->size--;
    return aux;
  }
  else
  {
    node_t* aux = deque->rear;
    deque->rear = aux->prev;
    deque->rear->next = aux->next;
    aux->prev = NULL;
    deque->size--;
    return aux;
  }

}
//Retira o valor da frente caso nao esteja vazia
node_t* dequeue_front(deque_t *deque)
{
   if(deque->size == 0)
  {
    return NULL;
  }
  if(deque->size == 1)
  {
    node_t* aux = deque->front;
    deque->rear = NULL;
    deque->front = NULL;
    deque->size--;
    return aux;
  }
  else
  {
    node_t* aux = deque->front;
    deque->front = aux->next;
    deque->front->prev = aux->prev;
    aux->next = NULL;
    deque->size--;
    return aux;
  }
}
//Limpa o conteudo do deque(deixa ele vazio)
void erase(deque_t *deque)
{
  while(deque->front != NULL && deque->rear != NULL)
  {
    dequeue_rear(deque);
  }
}
//Imprime o deque em uma unica linha, com os elementos separados por um espa�o,
//terminando com um \n, lembrando de respeitar os conceitos de fila.
void print(deque_t *deque)
{
  if(deque->front == NULL)
  {
    printf("EMPTY DEQUE\n");
    return;
  }
  node_t* first = deque->front;//para n�o alterarmos a head da fila
  while(first != NULL)
  {
    if(first->next == NULL)
    {
      printf("%d\n", first->value);
      first = first->next;
    }
    else
    {
      printf("%d ", first->value);
      first = first->next;
    }
  }
}
int main()
{
  deque_t *deque = construct();
  printf("Digitando 1 2 3 e 4 temos: ");
  enqueue_rear(deque, 1);
  enqueue_rear(deque, 2);
  enqueue_rear(deque, 3);
  enqueue_rear(deque, 4);
  //digitamos 1, 2, 3 e 4
  print(deque);
  //deque auxiliar para guardar os Ctrl Z
  deque_t *aux = construct();
  node_t *p;
  //Primeiro Ctrl Z
  printf("Primeiro Ctrl Z: ");
  p = dequeue_rear(deque);
  print(deque);
  enqueue_front(aux, p->value);
  printf("Deque com o que foi retirado: ");
  print(aux);
  free(p);
  //Segundo Ctrl Z
  p = dequeue_rear(deque);
  printf("Segundo Ctrl Z: ");
  print(deque);
  enqueue_front(aux, p->value);
  printf("Deque com o que foi retirado: ");
  print(aux);
  free(p);
  //Primeiro Ctrl Y
  printf("Primeiro Ctrl Y: ");
  enqueue_rear(deque, aux->front->value);
  print(deque); 
  p = dequeue_front(aux);
  free(p);
  //Segundo Ctrl Y
  printf("Segundo Ctrl Y: ");
  enqueue_rear(deque, aux->front->value);
  printf("Deque com o que foi retirado:\n");
  print(deque);
  p = dequeue_front(aux);
  print(aux);
  free(p);
  return 0;
}