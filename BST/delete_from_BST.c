#include<stdio.h>
#include<stdlib.h>

/*the objective of this code is to create and display the following BST recursivly and then delete any node from it
                20
               /  \
              8   30
             / \
            5  10
*/

struct node
{
    int data;
    struct node *left_ptr;
    struct node *right_ptr;
} *root=NULL;


int height(struct node *);
struct node *recursive_insert(struct node *, int);
void inorder(struct node *);
struct node *delete(struct node *, int);
struct node *inorder_succ(struct node *);
struct node *inorder_pre(struct node *);


int main(){

    root=recursive_insert(root,20);
    recursive_insert(root,9);
    recursive_insert(root,5);
    recursive_insert(root,30);
    recursive_insert(root,8);

    printf("\n BST (inorder)");
    inorder(root);

    printf("\n\n*************** DELETE FUNCTION TEST *************");
    delete(root,20);
    inorder(root);
    printf("\n\n THE NODE WAS DELETED SUCCESFULLY\n\n");

    return 0;
}

//creat our BST

struct node *recursive_insert(struct node *p, int key){

    struct node *t=root;
    if (p==NULL)
    {
        t=malloc(sizeof(struct node));
        t->data=key;
        t->left_ptr=t->right_ptr=NULL;
        return t;
    }

    if (key<p->data)
    {
        p->left_ptr=recursive_insert(p->left_ptr,key);
    }
    else if (key>p->data)
    {
        p->right_ptr=recursive_insert(p->right_ptr,key);
    }
    
    return p;  
}


//display the elements of the tree in inorder traversal

void inorder(struct node *p){

    if (p!=NULL)
    {
        inorder(p->left_ptr);
        printf("\n  %i",p->data);
        inorder(p->right_ptr);
    }
    
}

//delete from BST

struct node *delete(struct node *p, int key){

    struct node *q;

    //first check if p is a leaf node, if so simply free it

    if (p->left_ptr==NULL && p->right_ptr==NULL)
    {
        free(p);
        return NULL;
    }

    //if it is not a leaf node search for that node

    if (key<p->data)
    {
        p->left_ptr=delete(p->left_ptr,key);
    }
    else if (key>p->data)
    {
        p->right_ptr=delete(p->right_ptr,key);
    }
    else    //node found
    {
        /*when we delete a node we should replace it either with his inorder successor or precessor
        we will decide that based on the hight of the left and the right sub-trees
        */

       if (height(p->left_ptr) > height(p->right_ptr))
       {
            q=inorder_pre(p->left_ptr);     //find the precessor
            p->data=q->data;                //once we find it, copy the data of that precessor in the node we are about to delete
            p->left_ptr=delete(p->left_ptr,q->data);    //delete that node precessor
       }
       else
       {
            q=inorder_succ(p->right_ptr);     //find the succcessor
            p->data=q->data;                //copy the data of that successor in the p's data
            p->right_ptr=delete(p->right_ptr,q->data);        //delete that node successor
       }

    }

}


//find the height of left and right sub-trees

int height(struct node *p){
    
    int x=0, y=0;   //x for height of left sub-tree and y is for height of right sub-tree

    if (p==NULL)
    {
        return 0;
    }
    
    x=height(p->left_ptr);
    y=height(p->right_ptr);
}

//find the inorder precessor of the deleted node to replace it in case the height of left sub-tree is greater than the height of right sub-tree

struct node *inorder_pre(struct node *p){

    while (p!=NULL && p->right_ptr!=NULL)
    {
        p=p->right_ptr;
    }
    
    return p;
}

//find the inoreder successor of the deleted node to replace it in case the height of right sub-tree is greater than the height of left sub-tree

struct node *inorder_succ(struct node *p){

    while (p!=NULL && p->left_ptr!=NULL)
    {
        p=p->left_ptr;
    }
    
    return p;
}