#include <stdio.h>
#include <stdlib.h>

typedef struct binary_search_tree
{
	int item;
	struct binary_search_tree *right;
	struct binary_search_tree *left;
}binary_search_tree;

binary_search_tree* create_empty_bst()
{
	return NULL;
}

binary_search_tree* create_binary_search_tree(int item, binary_search_tree *left, binary_search_tree *right)
{
	binary_search_tree *new_binary_search_tree = (binary_search_tree*) malloc(sizeof(binary_search_tree));
	new_binary_search_tree->item = item;
	new_binary_search_tree->left = left;
	new_binary_search_tree->right = right;
	return new_binary_search_tree;
}

binary_search_tree* search(binary_search_tree *bt, int item)
{
	if (bt == NULL || bt->item == item)
	{
		return bt;
	}
	else if (bt->item > item)
	{
		return search(bt->left, item);
	}
	else
	{
		return search(bt->right, item);
	}
}

binary_search_tree* search_n_recursivo(binary_search_tree *bt, int item)
{
	binary_search_tree *aux = bt;
	while(aux != NULL)
	{
		if (aux->item == item)
		{
			break;
		}
		else if (aux->item > item)
		{
			aux = aux->left;
		}
		else
		{
			aux = aux->right;
		}
	}
	return aux;
}

binary_search_tree* add(binary_search_tree *bt, int item)
{
	if(bt == NULL)
	{
		bt = create_binary_search_tree(item, NULL, NULL);
	}
	else if(bt->item > item)
	{
		bt->left = add(bt->left, item);
	}
	else
	{
		bt->right = add(bt->right, item);
	}
	return bt;
}
//retorna o item do node de menor valor de uma BST
int menor_node(binary_search_tree *bt)
{
	binary_search_tree *current = bt;
	while(current->left != NULL)
	{
		current = current->left;
	}
	return current->item;
}

binary_search_tree* remove_node(binary_search_tree *bt, int item)
{
	if(bt == NULL)return bt;
	if(bt->item > item)
	{
		bt->left = remove_node(bt->left, item);
	}
	else if(bt->item < item)
	{
		bt->right = remove_node(bt->right, item);
	}
	else
	{
		//node com 1 ou 0 filhos
		if(bt->right == NULL)
		{
			binary_search_tree *aux = bt->left;
			free(bt);
			return aux;
		}
		else if(bt->left == NULL)
		{
			binary_search_tree *aux = bt->right;
			free(bt);
			return aux;
		}
		//node com 2 filhos
		//nos dá o menor node da sub tree a direita do bt
		int aux = menor_node(bt->right); 
		bt->item = aux;
		bt->right = remove_node(bt->right, aux);
	}

	return bt;
}
void print_pre_order(binary_search_tree *bt)
{
	
	if (bt != NULL)
	{
		printf("%d ", bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}

int main()
{
	binary_search_tree *bt = create_empty_bst();	
	bt =  add(bt, 50);			
	bt =  add(bt, 30);
	bt =  add(bt, 20);		
	bt =  add(bt, 40);	
	bt =  add(bt, 70);
	bt =  add(bt, 60);
	bt =  add(bt, 80);	
	bt = remove_node(bt, 50);
	//queremos achar o node 30
	binary_search_tree *node;
	print_pre_order(bt);
	return 0;
}