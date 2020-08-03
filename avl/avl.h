#ifndef AVLTREE
#define AVLTREE
 
typedef struct bst{
    int nData;
    struct bst *pLeft;
    struct bst *pRight;
    int height;
}bst;

bst *BST_new(int data);
void BST_inorder(bst *root);
void BST_prerder(bst *root);

int BST_getHeight(bst *root);
int BST_getBalance(bst *node);

bst *BST_successor(bst *node);
bst *BST_predecessor(bst *node);

void BST_rightRotate(bst **ppNode);
void BST_leftRotate(bst **ppNode);

void BST_add(bst **ppRoot, int data);
void BST_remove(bst **ppRoot, int data);

void BST_rebalance(bst **ppNode);

#endif