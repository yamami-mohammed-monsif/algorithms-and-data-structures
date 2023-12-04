#include<stdio.h>
#include<stdlib.h>

//the objective is to generate an AVL tree.

struct node
{
    struct node *left_ptr;
    int data;
    struct node *right_ptr;
    int height;
}*root=NULL;


struct node * insert(struct node *, int);
void inorder(struct node *);
int node_height(struct node *);
int balance_factor(struct node *);
struct node * LLrotation(struct node *);
struct node * RRrotation(struct node *);
struct node * LRrotation(struct node *);
struct node * RLrotation(struct node *);



int main(){

    root=insert(root,10);
    insert(root,20);
    insert(root,30);
    insert(root,25);
    insert(root,28);
    
    printf("inorder traversal: \n");
    inorder(root);

    return 0;
}

//gnerate BST and balance it
struct node * insert(struct node *p, int key){
    if (p == NULL)
    {
        struct node *t = malloc(sizeof(struct node));
        t->data = key;
        t->height = 0;
        t->left_ptr = t->right_ptr = NULL;
        return t;
    }

    if (key < p->data)
    {
        p->left_ptr = insert(p->left_ptr, key);
    }
    else if (key > p->data)
    {
        p->right_ptr = insert(p->right_ptr, key);
    }

    // Update the height of the ancestor node (this happens in the return of recursion)
    p->height = node_height(p);
    
    //check if the node became imbalanced by checking the balance factor and apply the appropriate rotation type;
    if (balance_factor(p)==2 && balance_factor(p->left_ptr)==1)
    {
        return LLrotation(p);
    }
    else if (balance_factor(p)==-2 && balance_factor(p->left_ptr)==-1)
    {
        return RRrotation(p);
    }
    else if (balance_factor(p)==2 && balance_factor(p->left_ptr)==-1)
    {
        return LRrotation(p);
    }
    else if (balance_factor(p)==-2 && balance_factor(p->left_ptr)==1)
    {
        return RLrotation(p);
    }
    
    return p;
}

//inorder traversal display
void inorder(struct node *p){

    if (p!=NULL)
    {
        inorder(p->left_ptr);
        printf("\t %i   ",p->data);
        inorder(p->right_ptr);
    }
    
}


//calcualte the height of node
int node_height(struct node *p){
    
    int hl,hr;      //height left sub tree and height right sub tree
    hl= p && p->left_ptr ? p->left_ptr->height : 0;
    hr= p && p->right_ptr ? p->right_ptr->height : 0;

    return hl>hr ? hl+1 : hr+1;
}

//find the ballance factor
int balance_factor(struct node *p){

    int hl,hr;
    hl= p && p->left_ptr ? p->left_ptr->height : 0;
    hr= p && p->right_ptr ? p->right_ptr->height : 0;

    return hl - hr;
}

//LL rotation
struct node * LLrotation(struct node *p){
    
    struct node *pl=p->left_ptr;
    struct node *plr=pl->right_ptr;

    //performe rotation
    pl->right_ptr=p;
    p->left_ptr=plr;

    //update height
    p->height=node_height(p);
    pl->height=node_height(pl);

    //if the rotation was performed on the root we will have a new root (return it)
    if (p==root)
    {
        return pl;
    } 
}

//RR rotation
struct node * RRrotation(struct node *p){

    struct node *pr=p->right_ptr;
    struct node *prl=pr->left_ptr;

    //performe rotation
    pr->left_ptr=p;
    p->right_ptr=prl;

    //update height
    p->height=node_height(p);
    pr->height=node_height(pr);

    if (p==root)
    {
        return pr;
    } 
}

//LR rotation
struct node * LRrotation(struct node *p){

    struct node *pl=p->left_ptr;
    struct node *plr=pl->right_ptr;

    plr->right_ptr=p;
    plr->left_ptr=pl;

    p->height=node_height(p);
    pl->height=node_height(pl);
    plr->height=node_height(plr);

    if (p==root)
    {
        return plr;
    }
}

//RL rotation
struct node * RLrotation(struct node *p){

    struct node *pr=p->right_ptr;
    struct node *prl=pr->left_ptr;

    prl->left_ptr=p;
    prl->right_ptr=pr;

    p->height=node_height(p);
    pr->height=node_height(pr);
    prl->height=node_height(prl);

    if (p==root)
    {
        return prl;
    }

}
