#include<stdio.h>
#include<stdlib.h>

/*the objective of this code is to create and display the following BST
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

void insert(int);
void inorder(struct node*);
struct node* search(int);

int main(){

    insert(10);
    insert(5);
    insert(20);
    insert(8);
    insert(30);

    printf("\n BST (inorder)");
    inorder(root);

    struct node *temp;      //we need a temp var for taking the result from search

    temp= search(55);
    printf("\n\n**************************\n the result of the search: ");
    if (temp!=NULL)
    {
        printf("\n\n element %i is found",temp->data);
    }
    else
        printf("\n\n element not found");
    
    return 0;
}


void insert(int key){

    struct node *t=root;
    struct node *r,*p;      //pointer r is a tail pointer following the pointer t and p helps in  creating new nodes

    if (root==NULL)          //creating the first node the root
    {
        p=malloc(sizeof(struct node));           //create new node using pointer p and set its data to key and right and left pointers to null
        p->data=key;
        p->left_ptr=p->right_ptr=NULL;
        root=p;          //pointer root should be pointing upon this node
        return; 
    }

    while (t!=NULL)         //here we start adding nodes to our tree 
    {
        r=t;
        if (key<t->data)
        {
            t=t->left_ptr;
        }
        else
            t=t->right_ptr; 
    }

    p=malloc(sizeof(struct node));
    p->data=key;
    p->left_ptr=p->right_ptr=NULL;
    
    if (key<r->data)        //here our node is already created but we should check again to know where this node should be linked left or right
    {
        r->left_ptr=p;
    }
    else
        r->right_ptr=p;
}



void inorder(struct node *p){      //display the elements of the tree in inorder traversal

    if (p!=NULL)
    {
        inorder(p->left_ptr);
        printf("\n  %i",p->data);
        inorder(p->right_ptr);
    }
    
}


    //i added a function that searches for a key element in BST
struct node* search(int key){

    struct node *t=root;        //we need a pointer that starts from the root
    while (t!=NULL)
    {
        if (key==t->data)
        {
            return t;
        }
        else if (key<t->data)
        {
            t=t->left_ptr;
        }
        else
            t=t->right_ptr;    
    }
    return NULL;  
}