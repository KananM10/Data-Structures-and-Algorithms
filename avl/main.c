#include <stdio.h>
#include "avl.h"

void main()
{
    struct bst *root = BST_new(5);

    BST_add(&root, 2);
    BST_add(&root, 1);
    BST_add(&root, 3);
    BST_add(&root, 6);

    BST_prerder(root);
    puts("\n");

    BST_rightRotate(&root);

    BST_prerder(root);
    puts("");

    BST_leftRotate(&root);

    BST_prerder(root);
    puts("");
}