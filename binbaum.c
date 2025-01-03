#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*typedef union {
    int zahl;
    double kommazahl;
    char* Stringpointer;
} data;
*/
struct tree{
    struct tree *nachfolgerR;
    struct tree *nachfolgerL;
    int data;
};
typedef struct tree tree;

tree* newTree(int input);
tree* insert(tree* node, int input);
tree* search(tree* node, int input);
void preorder(tree* node);
void inorder(tree* node);
void postorder(tree* node);
void treeFree(tree* node);

int main()
{
    srand(time(0)); //declares seed
    //test tree
    tree* root = NULL;
    root = insert(root, 50);
    for(int i = 0; i < 10; i++)
    {
        int random = rand()%100 +1;
        root = insert(root, random);
    }
    root = insert(root, 70);
    printf("Inorder:\n");
    inorder(root);
    printf("preorder:\n");
    preorder(root);
    printf("search function: search 70: %d", search(root, 70)->data);

    treeFree(root);
    return 0;
}

tree* newTree(int input)
{
    tree *tmp = (tree *) malloc(sizeof(tree));
    tmp->data = input;
    tmp->nachfolgerL = NULL;
    tmp->nachfolgerR = NULL;
    return tmp;
}
tree* insert(tree* node, int input)
{
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
    
    return node;
}

tree* search(tree* node, int input)
{
    if(node == NULL)
    {
        return NULL;
    }
    if(node->data == input)
    {
        return node;
    }
    else
    {
        if(input < node->data)
        {
            return search(node->nachfolgerL, input);
        }
        else
        {
            return search(node->nachfolgerR, input);
        }
    }
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

void postorder(tree* node)
{
    if(node == NULL)
    {
        return;
    }
    postorder(node->nachfolgerL);
    postorder(node->nachfolgerR);
    printf("%d\t", node->data);
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
