#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree
{
	int item;
	struct binary_tree *right;
	struct binary_tree *left;
}binary_tree;

binary_tree* create_empty_bt()
{
	return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
	binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
	new_binary_tree->item = item;
	new_binary_tree->left = left;
	new_binary_tree->right = right;
	return new_binary_tree;
}
int is_empty(binary_tree *bt)
{
	return(bt == NULL);
}
void print_pre_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		printf("%d ", bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}
void print_in_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		print_in_order(bt->left);
		printf("%d ", bt->item);
		print_in_order(bt->right);
	}
}
void print_pos_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		print_pos_order(bt->left);
		print_pos_order(bt->right);
		printf("%d ", bt->item);
	}
}
int main()
{
	binary_tree *bt = create_binary_tree(6, create_binary_tree(4, NULL, NULL), create_binary_tree(9,create_binary_tree(1, NULL, NULL), create_binary_tree(2, NULL, NULL)));
	print_in_order(bt);
	printf("\n");

	return 0;
}