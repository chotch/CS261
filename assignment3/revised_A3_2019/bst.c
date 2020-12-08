#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "linkedListStack.h"

struct node{
   TYPE value;
   struct node *left;
   struct node *right;
};

struct BSTree{
   struct node *root;
   int size;
};

/*
 * This is the structure you will use to create an in-order BST iterator.  It
 * is up to you how to define this structure.
 */

struct BSTreeIterator{
/* TODO: Define an iterator for a binary search tree; */
	struct BSTree * myTree;
	struct node* currentNode;
	struct LinkedList * myStack;
};


struct BSTree*  initBSTree()
{
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != 0);
    tree->size  = 0;
    tree->root = 0;
    return tree;
}


struct node *BSTnodeAdd(struct node *root, TYPE newValue)
{
 /* End condition */
   if (!root)
   {
       root = malloc(sizeof(struct node));
       assert(root);
       root -> value = newValue;
       root -> left = 0;
       root -> right = 0;
       return root;
   }
 /* 2: Recursion */
   if (root -> value > newValue)
   {
       /* Go left */
       root -> left = BSTnodeAdd(root->left, newValue);
       /* root -> left = root -> left; */
   }
   if (root -> value < newValue)
   {  /* Go right */
       root -> right = BSTnodeAdd(root->right, newValue);
   }

   if (root -> value == newValue)
   {
       root = root;
      /* Several options: 1) Throw error (extreme); 2) Keep the tree as-is; 3) Define to either go left or right in this case */
   }
/* 3: Return value */
   return root;
}

void BSTAdd(struct BSTree *tree, TYPE newValue) {
     tree->root = BSTnodeAdd(tree->root, newValue); 
     tree->size++; 
 }

TYPE _leftMostChild (struct node * current) { 
     assert(current); 
  /* 1: end condition */
     if (!current -> left)
         return current -> value;
  /* 2: recursion */
  /* 3: return value */
     return _leftMostChild(current -> left);
}

struct node * _removeLeftMostChild (struct node *current) { 
/* 1: end condition */
   if (! current -> left)
   {
       struct node *new_left;
       new_left = current -> right;
       free(current);
       return new_left;
   }

/* 2: recursion */
    current -> left = _removeLeftMostChild(current -> left);
/* 3: return value */
    return current;
}

struct node * _BSTNodeRemove (struct node * current, TYPE d) { 
    
/* 1: End condition:
   Suppose we are already at the node we want to remove */
   if ( current -> value == d)
   {
/* 1) If current has a right child */
/* Replace it with the leftmost child on right side */
       if (current -> right)
       {
           current -> value = _leftMostChild(current -> right);
           current -> right = _removeLeftMostChild(current -> right);
           return current;
       }
/* 2) If current does not have a right child */
       else
       {
           struct node *temp = current -> left;
           free(current);
           return temp;
       }
   }
/* 2: Recursion */
   if (current -> value > d)
       current -> left = _BSTNodeRemove(current -> left, d);
   if (current -> value < d)
       current -> right = _BSTNodeRemove(current -> right, d);
/* 3: return value */
   return current;
}

struct BSTree *buildBSTree() {
    struct BSTree *tree	= initBSTree();		
		
    /*Create value of the type of data that you want to store*/
	
    /*add the values to BST*/
	/* This tree can be found in Slide 24 of the BST slides */
    BSTAdd(tree, 50);
    BSTAdd(tree, 25);
    BSTAdd(tree, 75);
    BSTAdd(tree, 35);
    BSTAdd(tree, 20);
    BSTAdd(tree, 60);
    BSTAdd(tree, 20);
    BSTAdd(tree, 60);
    BSTAdd(tree, 35);
    BSTAdd(tree, 20);
    BSTAdd(tree, 60);
    BSTAdd(tree, 65);
    BSTAdd(tree, 45);
    BSTAdd(tree, 30);
    BSTAdd(tree, 85);
    BSTAdd(tree, 80);
    
    return tree;
}

/*
  This function recursively frees all the nodes of a binary search tree
  param: node  the root node of the tree to be freed
  pre: none
  post: node and all descendants are deallocated
*/

void _freeBST(struct node *node)
{

	if (node == NULL)
		return;
	
	_freeBST(node->left);
	_freeBST(node->right);

	printf("Freeing the value: %d \n", node->value);
	free(node);


/* TODO: Complete this implementation */
}


void deleteBSTree(struct BSTree *bstree)
{
    _freeBST(bstree->root);
    bstree->root = 0;
    free(bstree);
}

/*
  This function recursively print all nodes in the tree by completing an in-order
  traversal. Please print the tree in this format:
  
  for every subtree, start it with a (, and end it with a ), in the middle, print the subtree values one-by-one.
  
  e.g.,a tree with just root = 50 should be (50)
  a tree with root = 50, root->left = 30 and root->right = 70 should be ((30) 50 (70))
  a tree with root = 50, root->left = 30, root->left->left = 20, root -> left->right = 40, root->right = 70 should be (((20) 30 (40)) 50 (70))

  param: node: the root node of the tree to be printed
  pre: none
  post: the tree is printed */

void _printNode(struct node *node) {

	if (node == NULL)
		return;
	
	printf("(");
	_printNode(node->left);
	
	//printf(" ( ");
	printf("%d", node->value);
	//printf(")");
	_printNode(node->right);	
	printf(")");
/* TODO: Complete this implementation */
}

void printBSTree(struct BSTree *tree) {
    if (tree == 0)
	return;	 
    _printNode(tree->root);	 
    printf("\n");
}



/*
 * This function should allocate and initialize a new in-order BST iterator
 * given a specific BST over which to iterate.
 *
 * Params:
 *   bst - the BST over which to perform in-order iteration.  May not be NULL.
 *
 * Return:
 *   Should return a pointer to a new in-order BST iterator, initialized so
 */
struct BSTreeIterator* BSTIteratorCreate(struct BSTree* tree) {
/* TODO: Complete this implementation */
	struct BSTreeIterator * myIterator = malloc(sizeof(struct BSTreeIterator));
	myIterator->myTree = tree;
	myIterator->myStack = createLinkedList();
	if (tree->root == NULL){
		myIterator->currentNode = NULL;
		return myIterator;
	}

	if (tree->root->left == NULL){
		myIterator->currentNode = tree->root;
//		pushLinkedList(myIterator->myStack, myIterator->currentNode);
		return myIterator;
	}

	myIterator->currentNode = tree->root;
//	pushLinkedList(myIterator->myStack, myIterator->currentNode);	
	
	if (myIterator->currentNode->left->left != NULL){
		pushLinkedList(myIterator->myStack, myIterator->currentNode);

		while(myIterator->currentNode->left->left != NULL){
			myIterator->currentNode = myIterator->currentNode->left;
	//		pushLinkedList(myIterator->myStack, myIterator->currentNode);
		}
	}

	return myIterator;
}

/*
 * This function should free all memory allocated to a BST iterator.
 *
 * Params:
 *   iter - the iterator whose memory is to be freed.  May not be NULL.
 */
void BSTIteratorFree(struct BSTreeIterator* iter) {
/* TODO: Complete this implementation */
	assert(iter && iter->myStack);
	free(iter->myStack);
	free(iter);
}


/*
 * This function should return 1 if there is at least one more node to visit
 * in the in-order iteration of the BST represented by a given iterator.  If
 * there are no more nodes to visit, it should return 0.
 *
 * Params:
 *   iter - the iterator to be checked for more values.  May not be NULL.
 */
int BSTIteratorHasNext(struct BSTreeIterator* iter) {
/* TODO: Complete this implementation */
//	return 1;
	return !isEmptyLinkedList(iter->myStack) ||  iter->currentNode != NULL;

/*	if (BSTIteratorNext(iter) == iter->myTree->root)
		return 0;
	else
		return 1;*/
}


/*
 * This function should return the next value in the in-order iteration of the
 * BST represented by a given iterator.
 *
 * Params:
 *   iter - the iterator whose next value is to be returned.  May not be NULL
 *     and must have at least one more value to be returned.
 */
int BSTIteratorNext(struct BSTreeIterator* iter) {
	
	int returnVal = 0;

	//traverse down left branch... adding each visited parent to stack	
	while (iter->currentNode != NULL){
		pushLinkedList(iter->myStack, iter->currentNode);
		iter->currentNode = iter->currentNode->left;
	}

	//set current node to be top of the item in stack and pop off the value
	iter->currentNode = topLinkedList(iter->myStack);
	popLinkedList(iter->myStack);


	//set current node to be right child of current to proceed down right path if it exists
	returnVal = iter->currentNode->value;
	iter->currentNode = iter->currentNode->right;

	return returnVal;	

	/*int returnVal = 0;	
	struct node * tempNode = topLinkedList(iter->myStack);

	
	popLinkedList(iter->myStack);
	
	if (tempNode->right != NULL){
		tempNode = tempNode->right;
		pushLinkedList(iter->myStack, tempNode);
	}


	while (tempNode->left != NULL){
		pushLinkedList(iter->myStack, tempNode);
		tempNode = tempNode->left;
	}
	
	returnVal = tempNode->value;
	free(tempNode);
	return tempNode->value;
*/	
/*	while (iter->currentNode->left != NULL){
		iter->currentNode = iter->currentNode->left;
		pushLinkedList(iter->myStack, iter->currentNode);	
	
	}
	popLinkedList(iter->myStack);
	return iter->currentNode->value; */

	
/* TODO: Complete this implementation */
}


void testIterator(int tree_num){
	struct BSTree *tree;
	if (tree_num == 1)
		tree=buildBSTree();
	if (tree_num == 2)
		tree=initBSTree();
	if (tree_num == 3){
		tree = initBSTree();
		BSTAdd(tree,10);
	}
	if (tree_num == 4)
	{
		tree = initBSTree();
		BSTAdd(tree, 10);
		BSTAdd(tree, 5);
	}
    struct BSTreeIterator* iter = BSTIteratorCreate(tree);

//ME TESTING 
/*	struct node * temp = topLinkedList(iter->myStack);
	printf("%d", (temp->value));	
printf("%d", iter->currentNode->value); //correctly starts off pointing to left most value
	popLinkedList(iter->myStack);
	temp = topLinkedList(iter->myStack);
	printf("%d", temp->value);
	popLinkedList(iter->myStack);
	//temp = topLinkedList(iter->myStack);
	//printf("%d", temp->value);
	//popLinkedList(iter->myStack);
	if (isEmptyLinkedList(iter->myStack) == 1){
		printf("is now empty");
	}*/
//GIVEN CODE
    printf("\n== BST contents (in order):");
    while (BSTIteratorHasNext(iter)) {
        int val = BSTIteratorNext(iter);
        printf(" %4d", val);
    }
    printf("\n");
	/* Result from not using the iterator */
    printf("Baseline comparison:\n");
	printBSTree(tree);
    BSTIteratorFree(iter);
	deleteBSTree(tree);
}

/*

  Main function for testing different functions of the Assignment #3.

*/

int main(int argc, char *argv[]){	
	
	/* Simple cases are usually likely to be corner cases, hence besides a normal tree, we should also test with simple cases */
	
	/* Test #1: a normal tree */
   testIterator(1);
	/* Test #2: an empty tree */
   testIterator(2);
	/* Test #3: a tree with only root */
	testIterator(3);
	/* Test #4: a tree with root and a left child */
	testIterator(4);
	
    return 0;
}

