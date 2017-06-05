#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treestr TNODE;

struct treestr
{
    int tmp;
    TNODE *ltree;
    TNODE *rtree;
};

TNODE *addtree(int tmp);
void search(int searchtmp, TNODE *root, TNODE **x);
void SearchParent(TNODE *root, TNODE *child, TNODE **x);
void addch(TNODE *parent, int tmp);
void show(TNODE *tp, int Space);
void SaveTree(TNODE *root);
void LoadTree(TNODE **root);
void GetNode(TNODE **root, FILE **fp);
void SaveNode(TNODE *root, FILE **fp);
void DeleteTree(TNODE **root);
void Stats(TNODE *root, int *det, int *leav, int *fre, int *infre, int *hp, int flag);

int main()
{
    TNODE *tnode = NULL;
    TNODE *nodex;
    TNODE *nodey;
    char array[255];
    int tmp,searchtmp;
    int det, leav, fre, infre, hp, dlina;
    printf("Enter command: ");
    scanf("%s", array);
    while (strcmp(array,"exit")!=0)
    {
        nodex = NULL;
        nodey = NULL;
        if (strcmp(array,"add")==0)
        {
            scanf(" %s", &array);
            if (strcmp(array,"root")==0)
            {
                if (scanf(" %d", &tmp))
                    if (tnode==NULL)tnode=addtree(tmp);
                    else printf("Root already exists\n");
                else {printf("error\n");fflush(stdin);}
            }
            else
            if (strcmp(array,"node")==0)
            {
                if (scanf(" %d", &tmp))
                {
                    scanf(" %s", array);
                    search(tmp, tnode, &nodex);
                    if (nodex!=NULL)
                    {
                        printf("Node already exists\n");
                    }
                    else
                    {
                        if (strcmp(array,"parent")==0)
                        {
                            scanf(" %s", array);
                            if (searchtmp=atoi(array))
                            {
                                search(searchtmp, tnode, &nodex);
                                addch(nodex,tmp);
                                nodex=NULL;
                            }
                            else
                            if (strcmp(array,"root")==0)
                            {
                                addch(tnode,tmp);
                            }
                            else {printf("Syntax error\n");fflush(stdin);}
                        }
                        else
                        if (strcmp(array,"sibling")==0)
                        {
                            if (scanf(" %d", &searchtmp))
                            {
                                search(searchtmp, tnode, &nodex);
                                SearchParent(tnode, nodex, &nodey);
                                addch(nodey, tmp);
                                nodex=nodey=NULL;
                            }
                            else {printf("Syntax error\n");fflush(stdin);}
                        }
                        else {printf("Syntax error\n");fflush(stdin);}
                    }
                }
                else {printf("Syntax error\n");fflush(stdin);}
            }
            else {printf("Syntax error\n");fflush(stdin);}
        }
        else
        if (strcmp(array,"show")==0)
        {
                if (tnode!= NULL)
                {
                    Stats(tnode, &det, &leav, &fre, &infre, &hp,0);
                    show(tnode,1);
                    putchar('\n');
                }
                else printf("Tree is empty\n");
        }
        else
        if (strcmp(array,"save")==0)
        {
            SaveTree(tnode);
        }
        else
        if (strcmp(array,"load")==0)
        {
            LoadTree(&tnode);
        }
        else
        if (strcmp(array,"delete")==0)
        {
            scanf(" %s", array);
            if (strcmp(array,"tree")==0)
                DeleteTree(&tnode);
            else
            if (strcmp(array,"node")==0)
            {
                scanf(" %s", array);
                tmp=atoi(array);
                if (tmp)
                {
                    search(tmp, tnode, &nodex);
                    if (nodex == NULL) printf("Error. No such node.");
                    else if (tnode==nodex) DeleteTree(&tnode);
                    else
                    {
                        SearchParent(tnode, nodex, &nodey);
                        if (nodey->ltree==nodex)
                            nodey->ltree=NULL;
                        else nodey->rtree=NULL;
                        DeleteTree(&nodex);
                    }
                }
                else {printf("Syntax error\n");fflush(stdin);}
            }
            else {printf("Syntax error\n");fflush(stdin);}
        }
        else
        if (strcmp(array,"stats")==0)
        {
            Stats(tnode, &det, &leav, &fre, &infre, &hp,0);
            printf(" Tree det %d\n Leaves number %d\n fre %d\n Infre %d\n Isnot heap %d\n ",
                   det, leav, fre, infre, hp);
        }
        else
        if (strcmp(array,"help")==0)
        {
            printf("List of commands: \nadd root 'val'\n add node 'val' parent 'val"
                   "\n change 'val' to 'val'\n delete tree\ndelete node 'val'\nstats\nshow\n"
                   "save 'filename'\nload 'filename'\n");
        }
        else
        if (strcmp(array,"change")==0)
        {
                scanf(" %s", array);
                searchtmp=atoi(array);
                if (searchtmp)
                {
                    search(searchtmp, tnode, &nodex);
                    scanf(" %s", array);
                    if (strcmp(array,"to")==0)
                    {
                        scanf(" %s", array);
                        tmp=atoi(array);
                        if (tmp)
                        {
                            if (nodex)
                            {
                                search(tmp, tnode, &nodey);
                                if (nodey==NULL)
                                    nodex->tmp=tmp;
                                else printf("This value already exists\n");
                            }
                        }
                        else {printf("error\n");fflush(stdin);}
                    }
                    else {printf("error\n");fflush(stdin);}
                }
                else {printf("error\n");fflush(stdin);}
        }
        else {printf("error\n");fflush(stdin);}
        fflush(stdin);
        printf("Press any tmp\n");
        getchar();
        system("CLS");
        printf("Enter command  \n");
        scanf("%s", array);
    }
    return 0;
}
TNODE *addtree(int tmp)
{
    TNODE *tnodep;
    tnodep = (TNODE*) malloc (sizeof(TNODE));
    if (tnodep)
    {
        tnodep->tmp = tmp;
        tnodep->rtree = tnodep->ltree = NULL;
    }
    return tnodep;
}
void show(TNODE *tp, int space)
{
    int i;
    if (tp!=NULL)
    {
        show(tp->rtree,space+1);
        for (i=0; i<space; i++) printf("\t");
        printf("%d\n",tp->tmp);
        show(tp->ltree,space+1);
    }
}
void addch(TNODE *tnode, int tmp)
{
    if (tnode!=NULL)
    {
        if (tnode->ltree==NULL) tnode->ltree=addtree(tmp);
        else if (tnode->rtree==NULL) tnode->rtree=addtree(tmp);
        else printf("Error. No free children\n");
    }
    else printf("Error. Can not add to nonexistent node\n");
}
void search(int searchtmp, TNODE *root, TNODE **x)
{
    if (root!=NULL)
    {
        if (root->tmp==searchtmp) (*x)=root;
        else
        {
            if (root->ltree!=NULL) search(searchtmp, root->ltree, x);
            if (root->rtree!=NULL) search(searchtmp, root->rtree, x);
        }
    }
}
void SearchParent(TNODE *root, TNODE *child, TNODE **x)
{
    if ((child!=NULL)&&(root!=NULL))
    {
        if ((root->ltree==child)||(root->rtree==child)) (*x)=root;
        else
        {
            if  (root->ltree!=NULL) SearchParent(root->ltree, child, x);
            if  (root->rtree!=NULL) SearchParent(root->rtree, child, x);
        }
    }
    else printf("Error. Sib node does not exist\n");
}
void SaveTree(TNODE *root)
{
    char fname[255];
    FILE *fp;
    scanf(" %s",fname);
    fflush(stdin);
    fp=fopen(fname, "w");
    if (fp)
    {
        SaveNode(root, &fp);
        fclose(fp);
    }
    else printf("Error. Can not open file\n");
}
void LoadTree(TNODE **root)
{
    char fname[255];
    FILE *fp;
    scanf(" %s", fname);
    fflush(stdin);
    fp=fopen(fname, "r");
    if (fp)
    {
        GetNode(root, &fp);
        fclose(fp);
    }
    else printf("Error. Incorrect filename\n");
}
void GetNode(TNODE **root, FILE **fp)
{
    if (!feof(*fp))
    {
        (*root)= addtree(0);
        fread((*root),sizeof(TNODE),1,*fp);
        if ((*root)->ltree!=NULL) GetNode(&((*root)->ltree), fp);
        if ((*root)->rtree!=NULL) GetNode(&((*root)->rtree), fp);
    }
}
void SaveNode(TNODE *root, FILE **fp)
{
    if (root!=NULL)
    {
        fwrite(root, sizeof(TNODE),1,*fp);
        if (root->ltree!=NULL) SaveNode(root->ltree,fp);
        if (root->rtree!=NULL) SaveNode(root->rtree,fp);
    }
}
void DeleteTree(TNODE **root)
{
    if (*root!=NULL)
    {
        if ((*root)->ltree!=NULL) DeleteTree(&((*root)->ltree));
        if ((*root)->rtree!=NULL) DeleteTree(&((*root)->rtree));
        if (((*root)->ltree==NULL) && ((*root)->rtree==NULL))
        {
            free((*root)->ltree);
            free((*root)->ltree);
            (*root)=NULL;
        }
    }
    else printf("Tree is already empty\n");
}
void Stats(TNODE *root, int *det, int *leav, int *fre, int *infre, int *hp, int flag)
{
    static int curdet;
    if (flag==0) curdet=(*det)=(*leav)=(*fre)=(*infre)=(*hp)=0;
    if (root!=NULL)
    {
        (*fre)++;
        if ((root->ltree==NULL)&&(root->rtree==NULL)) (*leav)++;
        else (*infre)++;
        if (root->ltree!=NULL)
        {
            if (root->ltree->tmp>root->tmp) (*hp)=1;
            curdet++;
            Stats(root->ltree,det,leav,fre,infre,hp,1);
        }
        if (root->rtree!=NULL)
        {
            if (root->rtree->tmp>root->tmp) (*hp)=1;
            curdet++;
            Stats(root->rtree,det,leav,fre,infre,hp,1);
        }
    }
    if (curdet>(*det)) (*det)=curdet;
    curdet--;
}
