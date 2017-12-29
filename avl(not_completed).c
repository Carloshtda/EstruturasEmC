#include <stdio.h>
#include <stdlib.h>

typedef struct binary_search_tree
{
	int item;
	int h;
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
	new_binary_search_tree->h = 0;
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

int max(int a, int b)
{
	return (a > b) ? a : b;
}
 
int h(binary_search_tree *bt)
{
	if (bt == NULL)
	{
		return -1;
	}
	else
	{
		return 1 + max(h(bt->left), h(bt->right));
	}
}

int balance_factor(binary_search_tree *bt)
{
	if (bt == NULL)
	{
		return 0;
	}
	else if ((bt->left != NULL) && (bt->right != NULL))
	{
		return (bt->left->h - bt->right->h);
	}
	else if ((bt->left != NULL) && (bt->right == NULL))
	{
		return (1 + bt->left->h);
	}
	else
	{
		return(-(bt->right->h) - 1);
	}
} 

binary_search_tree* rotate_left(binary_search_tree *bt)
{
	binary_search_tree *subtree_root = NULL;
	if (bt != NULL && bt->right != NULL)
	{
		subtree_root = bt->right;
		bt->right = subtree_root->left;
		subtree_root->left = bt;
	}
	subtree_root->h = h(subtree_root);
	bt->h = h(bt);
	return subtree_root;
}

binary_search_tree* rotate_right(binary_search_tree *bt)
{
	binary_search_tree *subtree_root = NULL;
	if (bt != NULL && bt->left != NULL)
	{
		subtree_root = bt->left;
		bt->left = subtree_root->right;
		subtree_root->right = bt;
	}
	subtree_root->h = h(subtree_root);
	bt->h = h(bt);
	return subtree_root;
}



binary_search_tree* add(binary_search_tree *bt, int item)
{
	if(bt == NULL)
	{
		return create_binary_search_tree(item, NULL, NULL);
	}
	else if(bt->item > item)
	{
		bt->left = add(bt->left, item);
	}
	else
	{
		bt->right = add(bt->right, item);
	}
	bt->h = h(bt);
	binary_search_tree *child = NULL;

	if (balance_factor(bt) == 2 || balance_factor(bt) == -2)
	{
		if (balance_factor(bt) == 2)
		{
			child = bt->left;
			if (balance_factor(child) == -1)
			{
				bt->left = rotate_left(child);
			}
			bt = rotate_right(bt);
		}
		else if(balance_factor(bt) == -2)
		{
			child = bt->right;
			if (balance_factor(child) == 1)
			{
				bt->right = rotate_right(child);
			}
			bt = rotate_left(bt);
		}	
	}
	return bt;
}
//retorna o node de menor valor de uma BST
binary_search_tree* menor_node(binary_search_tree *bt)
{
	binary_search_tree *current = bt;
	while(current->left != NULL)
	{
		current = current->left;
	}
	return current;
}
//REMOVE AINDA NÃO IMPLEMENTADO!!!!
/*
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
		binary_search_tree *aux = menor_node(bt->right); 
		bt->item = aux -> item;
		bt->right = remove_node(bt->right, aux->item);
	}

	return bt;
}
*/
//REMOVE DANDO SEGMENTAL FAULT!!!!
/*
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
		binary_search_tree *aux = menor_node(bt->right); 
		bt->item = aux -> item;
		bt->right = remove_node(bt->right, aux->item);
	}

	if (bt == NULL)
	{
		return NULL;
	}

	bt->h = h(bt);
	binary_search_tree *child = NULL;

	if (balance_factor(bt) == 2 || balance_factor(bt) == -2)
	{
		if (balance_factor(bt) == 2)
		{
			child = bt->left;
			if (balance_factor(child) == -1)
			{
				bt->left = rotate_left(child);
			}
			bt = rotate_right(bt);
		}
		else if(balance_factor(bt) == -2)
		{
			child = bt->right;
			if (balance_factor(child) == 1)
			{
				bt->right = rotate_right(child);
			}
			bt = rotate_left(bt);
		}	
	}
	return bt;
}
*/
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
	bt =  add(bt, 51);			
	bt =  add(bt, 26);
	bt =  add(bt, 11);		
	bt =  add(bt, 6);	
	bt =  add(bt, 8);
	bt =  add(bt, 4);
	bt =  add(bt, 31);	
	bt = remove_node(bt, 26);
	print_pre_order(bt);
	return 0;
}