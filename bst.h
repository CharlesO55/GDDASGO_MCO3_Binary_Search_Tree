/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

//NOT ALLOWED TO EDIT FUNCTION PROTOTYPES TO TAKE IN POINTERS SO USE EXTERNALS INSTEAD
extern int nExternCounter;
//COUNTER WILL ONLY MONITOR SEARCHES. NOT TREE CREATION/INSTERTION

struct Node{
    int data;
    struct Node *pLeft;
    struct Node *pRight;
};

typedef struct Node sNode;

typedef struct {
	sNode *pRoot;	//POINTER to the ROOT Node of the binary search tree.
} bst;


//Returns an EMPTY bst.
bst* create() {
	//CREATE A BINARY TREE
	bst *pTree = malloc((int) sizeof(bst));
	pTree->pRoot = NULL;
	return pTree;
}

//Inserts a NEW node in the bst.
void insert(bst *t, int x) {
	//CREATE A NODE
	sNode *pNew = malloc((int) sizeof(sNode));
	pNew->data = x;
	pNew->pLeft = NULL;
	pNew->pRight = NULL;


	//PLACE THE NODE
	//SET AS ROOT IF TREE IS EMPTY
	if(t->pRoot == NULL){
		t->pRoot = pNew;
	}
	//ELSE ADD TO LEFT/RIGHT SUBTREES
	else{
		sNode *pCurrent = t->pRoot;
		while(1){
			//ADD LOWER/EQUAL TO LEFT SUBTREE WHEN SLOT IS AVAILABLE
			if(pNew->data <= pCurrent->data && pCurrent->pLeft == NULL){
				pCurrent->pLeft = pNew;
				break;
			}
			//WHEN NO SLOT AVAILABLE, CONTINUE TRAVERSING LEFT SUBTREE
			else if(pNew->data <= pCurrent->data && pCurrent->pLeft != NULL){
				pCurrent = pCurrent->pLeft;
			}
			//ADD HIGHER TO RIGHT SUBTREE
			else if (pNew->data > pCurrent->data && pCurrent->pRight == NULL){
				pCurrent->pRight = pNew;
				break;
			}
			//CONTINUE TRAVERSING RIGHT SUBTREE
			else{
				pCurrent = pCurrent->pRight;
			}
		}
	}
}

//Returns an sNode pointer to the node containing the value x. Returns NULL if the value x is NOT found in the bst
sNode* search(bst *t, int x) {
	sNode *pCurrent = t->pRoot;
	nExternCounter++;
	

	while (1){
		nExternCounter++;
		
		//COMPARE CURRENT
		if (x == pCurrent->data){
			return pCurrent;
		}
		//CONTINUE CHECKING LOWER LEFT
		else if (x < pCurrent->data && pCurrent->pLeft != NULL){
			pCurrent = pCurrent->pLeft;
		}
		//CONTINUE CHECKING HIGHER RIGHT
		else if (x > pCurrent->data && pCurrent->pRight != NULL){
			pCurrent = pCurrent->pRight;
		}
		//NO MORE CHILDREN CAN BE COMPARED
		else {
			return NULL;
		}
	}
}

//Prints the INORDER traversal of the bst rooted by the node pointed to by pPointer.
void inorder(sNode *pPointer) {
	nExternCounter++;
	
	//DO LEFT CHILD
	if (pPointer->pLeft != NULL){
		inorder(pPointer->pLeft);
	}

	//PROCESS THE CURRENT
	printf("%d ", pPointer->data);

	nExternCounter++;
	//DO RIGHT CHILD
	if (pPointer->pRight != NULL){
		inorder(pPointer->pRight);
	}
}

//Prints the PREORDER traversal of the bst rooted by the node pointed to by pPointer.
void preorder(sNode *pPointer) {
	
	//PROCESS THE CURRENT
	printf("%d ", pPointer->data);
	
	nExternCounter++;
	//THE LEFT
	if(pPointer->pLeft != NULL){
		preorder(pPointer->pLeft);
	}

	nExternCounter++;
	//THE RIGHT
	if(pPointer->pRight != NULL){
		preorder(pPointer->pRight);
	}
}

//Prints the POSTORDER traversal of the bst rooted by the node pointed to by pPointer.
void postorder(sNode *pPointer) {
	nExternCounter++;
	//DO LEFT CHILD
	if (pPointer->pLeft != NULL){
		postorder(pPointer->pLeft);	
	}
	nExternCounter++;
	//DO RIGHT CHILD
	if (pPointer->pRight != NULL){
		postorder(pPointer->pRight);
	}

	//PROCESS THE CURRENT
	printf("%d ", pPointer->data);
}

//Returns an sNode pointer to the node containing the LARGEST value in the bst rooted by the node pointed to by pPointer.
sNode* maximum(sNode *pPointer) {
	sNode *pCurrent = pPointer;
	nExternCounter++;

	//KEEP SELECTING LEFT SUBTREE
	while(pCurrent->pRight != NULL){
		nExternCounter++;
		pCurrent = pCurrent->pRight;
	}
	return pCurrent;
}

//Returns an sNode pointer to the node containing the SMALLEST value in the bst rooted by the node pointed to by pPointer.
sNode* minimum(sNode *pPointer) {
	sNode *pCurrent = pPointer;
	nExternCounter++;

	//KEEP SELECTING LEFT SUBTREE
	while(pCurrent->pLeft != NULL){
		nExternCounter++;
		pCurrent = pCurrent->pLeft;
	}
	return pCurrent;
}

//Returns an sNode pointer to the PARENT of the node containing the value x.
sNode* parent(bst *t, int x) {
	sNode *pCurrent = t->pRoot;
	nExternCounter++;
	sNode *pTarget = search(t, x);
	
	nExternCounter++;
	if (pTarget == NULL){
		printf("\n[PARENT]: ERROR TARGET CHILD COULD NOT BE FOUND");
		return NULL;
	}
	else if (pTarget == t->pRoot){
		printf("\n[PARENT]: ROOT HAS NO FURTHER PARENTS");
		return NULL;
	}

	while(1){
		nExternCounter++;
		if(pCurrent->pLeft == pTarget || pCurrent->pRight == pTarget)
			return pCurrent;
		else if (x <= pCurrent->data) {
			pCurrent = pCurrent->pLeft;
		}
		else {
			pCurrent = pCurrent->pRight;
		}
	}
}

//Returns an sNode pointer to the SUCCESSOR of the node containing the value x.
sNode* successor(bst *t, int x) {
	nExternCounter++;
	sNode *pTarget = search(t, x);

	if (pTarget == NULL){
		printf("\n[SUCCESSOR]: ERROR TARGET NOT FOUND");
		return NULL;
	}

	//WHEN RIGHT SUBTREE EXISTS. GET THE MINIMMUM OF RIGHT SUBTREE
	nExternCounter++;
	if(pTarget->pRight != NULL){
		return minimum(pTarget->pRight);
	}
	//SCAN THE ANCESTRY FOR AN ANCESTOR THAT POINTS LEFT
	else{
		while(1){
			//GET THE PARENT
			nExternCounter++;

			sNode *pParent = parent(t, pTarget->data);

			nExternCounter++;

			if (pParent->pLeft == pTarget)
				return pParent;

			//UPDATE THE CURRENT PARENT TO BE THE NEW TARGET FOR PARENT COMPARISSON
			pTarget = pParent;
		}
	}

}

//Returns an sNode pointer to the PREDECESSOR of the node containing the value x.
sNode* predecessor(bst *t, int x) {
	sNode *pTarget = search(t, x);

	nExternCounter++;
	if (pTarget == NULL){
		printf("\n[PREDECESSOR]: ERROR TARGET NOT FOUND");
		return NULL;
	}

	nExternCounter++;
	//WHEN LEFT SUBTREE EXISTS. GET THE MAXIMUM OF LEFT SUBTREE
	if(pTarget->pLeft != NULL){
		return maximum(pTarget->pLeft);
	}
	//SCAN FOR AN ANCESTOR THAT POINTS RIGHT TOWARDS TARGET'S ANCESTRY
	else{
		while(1){
			nExternCounter++;

			//GET THE PARENT
			sNode *pParent = parent(t, pTarget->data);
			
			nExternCounter++;
			if (pParent->pRight == pTarget)
				return pParent;
			
			//UPDATE THE CURRENT PARENT TO BE THE NEW TARGET FOR PARENT COMPARISSON
			pTarget = pParent;
		}
	}
}