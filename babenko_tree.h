
struct node {
	int value;
	struct node *left;
	struct node *right;
};




void destroy_tree(struct node* node) {
	if (node != 0) {

		destroy_tree(node->left);
		destroy_tree(node->right);
		free(node);
	}
}



void insert(int value, struct node** node) {
	struct node *temp = NULL;
	if(!(*node)) {
		temp = (struct node*)malloc(sizeof(struct node));
		temp->left = NULL;
		temp->right = NULL;
		temp->value = value;
		*node = temp;
		return;
	}
	
	else if (value < (*node)->value)
		insert(value, &(*node)->left);
	else if (value > (*node)->value)
		insert(value, &(*node)->right);
}



struct node* search(struct node** tree, int value) {
	if(!(*tree)) {
		
		return NULL;
	}
	if (value == (*tree)->value) {
		return *tree;
	}
	else if (value < (*tree)->value)
		search(&((*tree)->left), value);
	else if (value > (*tree)->value)
		search(&((*tree)->right), value);
	return NULL; 
}