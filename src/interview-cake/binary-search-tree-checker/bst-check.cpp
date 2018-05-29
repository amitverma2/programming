/*
 * Write a function to check that a binary tree is a valid binary search tree.
 */
#include<iostream>

bool debug = false;

typedef struct BSTNode_T {
    struct BSTNode_T * left;
    struct BSTNode_T * right;
    int value;
} BSTNode;

bool isBST(BSTNode *root, int *min, int *max)
{
    if(root->left == 0 &&
       root->right == 0) {
        *min = *max = root->value;
        return true;
    }
    // either left or right, or both are there
    int minL, maxL, minR, maxR;
    minL=maxL=minR=maxR=0;
    if(root->left)
    {
        // left is there
        if(!isBST(root->left, &minL, &maxL)) {
            if(debug) std::cout << "L: Left Subtree with value = " << root->left->value << " at node value = " << root->value << " is invalid BST." << std::endl;
            return false;
        }
        // left is a valid BST

        if(root->right)
        {
            // right is also there
            if(!isBST(root->right, &minR, &maxR)) {
                if(debug) std::cout << "LR: Right Subtree with value = " << root->right->value << " at node value = " << root->value << " is invalid BST." << std::endl;
                return false;
            }
            // right is a valid BST

            if(maxL >= root->value) {
                if(debug) std::cout << "LR: Tree at value = " << root->value << " is invalid BST because the maxL = " << maxL << " is >= its value." << std::endl;
                return false;
            }
            if(minR <= root->value) {
                if(debug) std::cout << "LR: Tree at value = " << root->value << " is invalid BST because the minR = " << minR << " is <= its value." << std::endl;
                return false;
            }

            *min = minL;
            *max = maxR;

            return true;
        }

        // left is there and is a valid BST but we don't have right subtree.
        if(maxL >= root->value) {
            if(debug) std::cout << "L: Tree at value = " << root->value << " is invalid BST because the maxL = " << maxL << " is >= its value." << std::endl;
            return false;
        }

        *min = minL;
        *max = maxL;

        return true;
    }
    // if we are here left subtree is not there
    // right should be there otherwise we would've hit the
    // leaf condition in the beginning of the function
    if(!isBST(root->right, &minR, &maxR)) {
        if(debug) std::cout << "R: Right subtree with value = " << root->right->value << " at node value = " << root->value << " is not a valid BST." << std::endl;
        return false;
    }

    if(minR <= root->value) {
        if(debug) std::cout << "R: Tree at value = " << root->value << " is invalid BST because the minR = " << minR << " is <= its value." << std::endl;
        return false;
    }

    *min = minR;
    *max = maxR;
    return true;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        debug = true;


    // hard work :(
    BSTNode n60, n20, n70, n90, n30, n80, n50;
    n60.value = 60; n60.left = n60.right = 0;
    n20.value = 20; n20.left = n20.right = 0;
    n70.value = 70; n70.left = n70.right = 0;
    n90.value = 90; n90.left = n90.right = 0;

    n30.value = 30; n30.left = &n20; n30.right = &n60;

    n80.value = 80; n80.left = &n70; n80.right = &n90;

    n50.value = 50; n50.left = &n30; n50.right = &n80;

    int min = 0;
    int max = 0;
    if(!isBST(&n50, &min, &max))
        std::cout << "Not a valid BST" << std::endl;
    else
        std::cout << "Is a valid BST, min = " << min << " max = " << max << std::endl;

    BSTNode n40;
    n40.value = 40; n40.left = n40.right = 0;

    n30.right = &n40; // this should make a valid BST;
    if(!isBST(&n50, &min, &max))
        std::cout << "Not a valid BST" << std::endl;
    else
        std::cout << "Is a valid BST, min = " << min << " max = " << max << std::endl;

    return 0;
}
