#include<stdio.h>
#include<stdlib.h>>

/*the objective of this code is to create and display the following BST recursivly
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
}*root=NULL;


struct node *recursive_insert(struct node *, int);
void inorder(struct node *);


int main(){

    root=recursive_insert(root,20);
    recursive_insert(root,10);
    recursive_insert(root,5);
    recursive_insert(root,30);
    recursive_insert(root,8);

    printf("\n BST (inorder)");
    inorder(root);

    return 0;
}


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


void inorder(struct node *p){      //display the elements of the tree in inorder traversal

    if (p!=NULL)
    {
        inorder(p->left_ptr);
        printf("\n  %i",p->data);
        inorder(p->right_ptr);
    }
    
}