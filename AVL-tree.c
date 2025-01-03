#include <stdio.h>
#include <stdlib.h>

struct tree{
    struct tree *nachfolgerR;
    struct tree *nachfolgerL;
    int data;
    int height;
};
typedef struct tree tree;

int getHeight(tree* node);
int max(int a, int b);
tree* newTree(int input);
tree* rightRotate(tree* node);
tree* leftRotate(tree* node);
int heightdif(tree* node);
tree* insert(tree* node, int input);
void preorder(tree* node);
void inorder(tree* node);
tree* deleteNode(tree* root, int key);
void treeFree(tree* node);

int main()
{
    tree* root = NULL;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Preorder:\n");
    preorder(root);
    root = deleteNode(root, 10);
    printf("preorder after 10 was deleted: \n");
    preorder(root);

    treeFree(root);
    return 0;
}

int getHeight(tree* node)
{
    if(node == NULL)
    {
        return 0;
    }
    return node->height;
}
int max(int a, int b)
{
    return (a > b)? a:b;
}

tree* newTree(int input)
{
    tree *tmp = (tree *) malloc(sizeof(tree));
    tmp->data = input;
    tmp->nachfolgerL = NULL;
    tmp->nachfolgerR = NULL;
    tmp->height = 1;
    return tmp;
}

tree* rightRotate(tree* node)
{
    tree* x = node->nachfolgerL;
    tree* y = x->nachfolgerR;
    //rotation
    x->nachfolgerR = node;
    node->nachfolgerL = y;

    //height 
    node->height = max(getHeight(node->nachfolgerL), getHeight(node->nachfolgerR)) + 1;
    x->height = max(getHeight(x->nachfolgerL), getHeight(x->nachfolgerR)) + 1;

    //return root
    return x;
}

tree* leftRotate(tree* node)
{
    tree* y = node->nachfolgerR;
    tree* x = y->nachfolgerL;
    //rotation
    y->nachfolgerL = node;
    node->nachfolgerR = x;

    //height
    node->height = max(getHeight(node->nachfolgerL), getHeight(node->nachfolgerR)) + 1;
    y->height = max(getHeight(y->nachfolgerL), getHeight(y->nachfolgerR)) + 1;

    //return root
    return y;
}

int heightdif(tree* node)
{
    if( node == NULL)
    {
        return 0;
    }
    return getHeight(node->nachfolgerL) - getHeight(node->nachfolgerR);
}

tree* insert(tree* node, int input)
{
    //standard bst insert 
    if(node == NULL)
    {
        return newTree(input);
    }
    if(input < node->data)
    {
        node->nachfolgerL = insert(node->nachfolgerL, input);
    }
    else if(input > node->data)
    {
       node->nachfolgerR = insert(node->nachfolgerR, input);
    }
    else
    {
        return node;
    }
    
    //update heights 
    node->height = 1 + max(getHeight(node->nachfolgerL), getHeight(node->nachfolgerR));

    //get balance
    int balance = heightdif(node);
    //if node is unbalanced:

    //4 cases 
    //1. left left
    if(balance > 1 && input < node->nachfolgerL->data)
    {
        return rightRotate(node);
    }
    //2. right right
    if(balance < -1 && input > node->nachfolgerR->data)
    {
        return leftRotate(node);
    }
    //3. left right 
    if(balance > 1 && input > node->nachfolgerL->data)
    {
        node->nachfolgerL = leftRotate(node->nachfolgerL);
        return rightRotate(node);
    }
    //4. right right 
    if(balance < -1 && input < node->nachfolgerR->data)
    {
        node->nachfolgerR = rightRotate(node->nachfolgerR);
        return leftRotate(node);
    }
    return node;

}
void preorder(tree* node)
{
    if(node == NULL)
    {
        return;
    }
    printf("%d\t", node->data);
    preorder(node->nachfolgerL);
    preorder(node->nachfolgerR);
}

void inorder(tree* node)
{
    if(node == NULL)
    {
        return;
    }
    inorder(node->nachfolgerL);
    printf("%d\t", node->data);
    inorder(node->nachfolgerR);
}
tree* minvalueNode(tree* node)
{
    tree* current = node;
    //loop down to find the leftmost leaf 
    while(current->nachfolgerL != NULL)
    {
        current = current->nachfolgerL;
    }
    return current;
}

tree* deleteNode(tree* root, int key)
{
    //standard deletion 
    if(root == NULL)
    {
        return root;
    }
    if(key < root->data)
    {
        root->nachfolgerL = deleteNode(root->nachfolgerL, key);
    }
    else if(key > root->data)
    {
        root->nachfolgerR = deleteNode(root->nachfolgerR, key);
    }
    else
    {
       //this is the node to be deleted 
       if(root->nachfolgerL == NULL || root->nachfolgerR == NULL)
       {
            tree* tmp = root->nachfolgerL ? root->nachfolgerL :
            root->nachfolgerR;
            //no children
            if(tmp == NULL)
            {
                tmp = root;
                root = NULL;
            }
            else
            {
                //one child
                *root = *tmp;
                free(tmp);
            }
        }
        else
        {
            //two children 
            tree* tmp = minvalueNode(root->nachfolgerR);
            root->data = tmp->data;
            root->nachfolgerR = deleteNode(root->nachfolgerR, tmp->data);

        }    

    }
    if(root == NULL)
    {
        return root;
    }
    root->height = 1 + max(getHeight(root->nachfolgerL), getHeight(root->nachfolgerR));
    //is node still balanced?
    int balance = heightdif(root);

    //4 cases 
    //left left 
    if(balance > 1 && heightdif(root->nachfolgerL) >= 0)
    {
        return rightRotate(root);
    }

    //left right 
    if(balance > 1 && heightdif(root->nachfolgerL) < 0)
    {
        root->nachfolgerL = leftRotate(root->nachfolgerL);
        return rightRotate(root);
    }
    //right right 
    if(balance < -1 && heightdif(root->nachfolgerR) <= 0)
    {
        return leftRotate(root);
    }
    //right left 
    if(balance < -1 && heightdif(root->nachfolgerR) > 0)
    {
        root->nachfolgerR = rightRotate(root->nachfolgerR);
        return leftRotate(root);
    }

    return root;
}

void treeFree(tree* node)
{
    if(node == NULL)
    {
        return;
    }
    treeFree(node->nachfolgerL);
    treeFree(node->nachfolgerR);
    free(node);
}