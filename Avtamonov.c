#include <stdio.h>
#include <stdlib.h>
 
typedef struct tree
  {
    int a;              
    struct tree *left;  
    struct tree *right; 
  } TREE;
 
TREE *add_to_tree(TREE *root, int new_value)
{
   if (root==NULL)  
     {
        root = (TREE*)malloc(sizeof(TREE));
        root->a = new_value;
        root->left = root->right = 0;
        return root;
     }
   if (root->a < new_value)          
     root->right = add_to_tree(root->right, new_value);
   else
     root->left  = add_to_tree(root->left,  new_value);
   return root;
}
 
void tree_to_array(TREE *root, int a[]) 
  {
    static max2=0;                      
    if (root==NULL) return;             
    tree_to_array(root->left, a);       
    a[max2++] = root->a;
    tree_to_array(root->right, a);      
    free(root);
  }
 
void sort_tree(int a[], int elem_total)        
{
   TREE *root;
   int i;
 
   root = NULL;
   for (i=0; i<elem_total; i++)        
      root = add_to_tree(root, a[i]);
   tree_to_array(root, a);            
}
 
void main() {
   int i;
   
   int a[19]={ 0,7,8,3,52,14,16,18,15,13,42,30,35,26 ,456, 5 ,78,99,12345};
 
   sort_tree(a, 19);
    
   printf("sorted array:\n");
   for (i=0;i<19;i++) printf("%d ",a[i]);   
}
