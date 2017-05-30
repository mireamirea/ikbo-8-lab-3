#include<stdio.h>
#include<stdlib>
struct tree {
  char info;
  struct tree *left;
  struct tree *right;
};
struct tree *stree(struct tree *root,struct tree *r,char info){
  if(!r) {
    r = (struct tree *) malloc(sizeof(struct tree));
    if(!r) {
      printf("Ќе хватает пам€ти\n");
      exit(0);
    }
    r->left = NULL;
    r->right = NULL;
    r->info = info;
    if(!root) return r; /* первый вход */
    if(info < root->info) root->left = r;
    else root->right = r;
    return r;
  }
  if(info < r->info)
    stree(r,r->left,info);
  else
    stree(r,r->right,info);

  return root;
}

struct tree *search_tree(struct tree *root, char key)
{
  if(!root) return root;  /* пустое дерево */
  while(root->info != key) {
    if(keyinfo) root = root->left;
    else root = root->right;
    if(root == NULL) break;
  }
  return root;
}

struct tree *dtree(struct tree *root, char key)
{
  struct tree *p,*p2;

  if(!root) return root; /* вершина не найдена */

  if(root->info == key) { /* удаление корн€ */
    /* это означает пустое дерево */
    if(root->left == root->right){
      free(root);
      return NULL;
    }
    /* или если одно из поддеревьев пустое */
    else if(root->left == NULL) {
      p = root->right;
      free(root);
      return p;
    }
    else if(root->right == NULL) {
      p = root->left;
      free(root);
      return p;
    }
    /* или есть оба поддерева */
    else {
      p2 = root->right;
      p = root->right;
      while(p->left) p = p->left;
      p->left = root->left;
      free(root);
      return p2;
    }
  }
  if(root->info < key) root->right = dtree(root->right, key);
  else root->left = dtree(root->left, key);
  return root;
}

void print_tree(struct tree *r, int l)
{
  int i;

  if(!r) return;

  print_tree(r->right, l+1);
  for(i=0; iinfo);
  print_tree(r->left, l+1);
}

struct tree *dtree(struct tree *root, char key)
{
  struct tree *p,*p2;

  if(!root) return root; /* вершина не найдена */

  if(root->info == key) { /* удаление корн€ */
    /* это означает пустое дерево */
    if(root->left == root->right){
      free(root);
      return NULL;
    }
    /* или если одно из поддеревьев пустое */
    else if(root->left == NULL) {
      p = root->right;
      free(root);
      return p;
    }
    else if(root->right == NULL) {
      p = root->left;
      free(root);
      return p;
    }
    /* или есть оба поддерева */
    else {
      p2 = root->right;
      p = root->right;
      while(p->left) p = p->left;
      p->left = root->left;
      free(root);
      return p2;
    }
  }
  if(root->info < key) root->right = dtree(root->right, key);
  else root->left = dtree(root->left, key);
  return root;
}
int main(void)
{
  char s[80];

  root = NULL;  /* инициализаци€ корн€ дерева */

  do {
    printf("¬ведите букву: ");
    gets(s);
    root = stree(root, root, *s);
  } while(*s);

  print_tree(root, 0);

  return 0;
}


