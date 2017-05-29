#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char** argv) {
	struct node* tree = NULL;
	int search_value;
	insert(10, &tree);
	insert(2, &tree);
	insert(1, &tree);
	printf("Search for: ");
	scanf("%d", &search_value);
	if(search(&tree, search_value))
		printf("Value %d found\n", search_value);
	else
		printf("Value %d not found\n", search_value);
	destroy_tree(tree);
	return 0;
}