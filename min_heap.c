#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 20
typedef struct heap
{
	int size;
	int data[MAX_HEAP_SIZE];
}heap;

heap* create_heap()
{
	int i;
	heap *new_heap = (heap*)malloc(sizeof(heap));
	for (i = 0; i < MAX_HEAP_SIZE; ++i)
	{
		new_heap->data[MAX_HEAP_SIZE] = 0;
	}
	new_heap->size = 0;
	return new_heap;
}

int get_parent_index(heap *heap, int i)
{
	return i >> 1;
}
int get_left_index(heap *heap, int i)
{
	return i << 1;
}
int get_right_index(heap *heap, int i)
{
	return (i << 1) + 1;
}
int item_of(heap *heap, int i)
{
	return heap->data[i];
}
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
void enqueue(heap *heap, int item)
{
	if(heap->size >= MAX_HEAP_SIZE)
	{
		printf("Heap overflow\n");
	}
	else
	{
		++heap->size;
		heap->data[heap->size] = item;
		
		int current_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);

		while(parent_index >= 1 && heap->data[current_index] < heap->data[parent_index])
		{
			swap(&heap->data[current_index], &heap->data[parent_index]);
			current_index = parent_index;
			parent_index = get_parent_index(heap, current_index);
		}
	}

}
 
void min_heapify(heap *heap, int i)
{
	int lowest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);
	if (left_index <= heap->size && heap->data[left_index] < heap->data[i])
	{
		lowest = left_index;
	}
	else
	{
		lowest = i;
	}
	if (right_index <= heap->size && heap->data[right_index] < heap->data[lowest])
	{
		lowest = right_index;
	}
	if (heap->data[i] != heap->data[lowest])
	{
		swap(&heap->data[i], &heap->data[lowest]);
		min_heapify(heap, lowest);
	}
}
int is_empty(heap *heap)
{
	if (heap->size == 0 )return 1;
	return 0;
}
int dequeue(heap *heap)
{
	if (is_empty(heap))
	{
		printf("Heap underflow\n");
		return -1;
	}
	else
	{
		int item = heap->data[1];
		
		heap->data[1] = heap->data[heap->size];
		heap->size--;
		
		min_heapify(heap, 1);
		
		return item;
	}
}
void heapsort(heap *heap)
{
	int	i;
	for (i = heap->size; i >= 2 ; --i)
	{
		swap(&heap->data[i], &heap->data[1]);

		heap->size--;
		min_heapify(heap, 1);
	}
}
void print_heap(heap *heap)
{
	if (is_empty(heap))
	{
		printf("Empty heap\n");
		return;
	}
	int i;
	for (i = 1; i <= heap->size; ++i)
	{
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}
int main()
{
	heap *new_heap = create_heap();
	enqueue(new_heap, 30);
	enqueue(new_heap, 50);
	enqueue(new_heap, 10);
	enqueue(new_heap, 20);
	enqueue(new_heap, 100);
	enqueue(new_heap, 80);
	print_heap(new_heap);
	heapsort(new_heap);
	int i;
	for (i = 1; i <= 6; ++i)
	{
		printf("%d\n", new_heap->data[i]);
	}
	return 0;
}