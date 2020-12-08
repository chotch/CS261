#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/*
 create a new circular list deque
 
	pre:    none
 	post:	returns pointer to allocated deque q, q->Sentinel is allocated and q->size equals zero
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *myList= malloc(sizeof(struct cirListDeque));
	assert(myList);
	struct DLink *Sentinel1 = malloc(sizeof(struct DLink));
	assert(Sentinel1);

	myList->Sentinel = Sentinel1;
	Sentinel1->next = NULL;
	Sentinel1->prev = NULL;
//	myList->Sentinel = Sentinel;
	myList->size = 0;
	myList->Sentinel->value = 0;

	return myList;
	/* FIXME: you must write this */
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* FIXME: you must write this */
	struct DLink *myLink = malloc(sizeof(struct DLink));
	myLink->value = val;
	myLink->next = NULL;
	myLink->prev = NULL;

	return myLink;
	/*temporary return value..you may need to change it*/	 

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	assert(q && lnk);
	struct DLink *newLink = _createLink(v);
	struct DLink *temp = lnk->next;

	lnk->next = newLink;
	newLink->prev = lnk;
	newLink->next = temp;
	temp->prev = newLink;

	q->size++;
	/* FIXME: you must write this */	 

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	assert(q);
	struct DLink *newLink = _createLink(val);
	assert(newLink);

	if (q->size >= 1){	
		struct DLink *nextNode = q->Sentinel->next;
//		assert(nextNode);

		while (nextNode->next != q->Sentinel){
			nextNode = nextNode->next;
		}

		nextNode->next = newLink;
		newLink->prev = nextNode;
		newLink->next = q->Sentinel;
		q->Sentinel->prev = newLink;
	}
	else {
		q->Sentinel->next = newLink;
		q->Sentinel->prev = newLink;
		newLink->prev = q->Sentinel;
		newLink->next = q->Sentinel;
	}

	/* FIXME: you must write this */	 
	q->size++;
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/

void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert(q);
	struct DLink *newLink = _createLink(val);
	assert(newLink);
	if (q->size >= 1){	
		struct DLink *temp = q->Sentinel->next;
		q->Sentinel->next = newLink;
	
		newLink->prev = q->Sentinel;
		newLink->next = temp; 
		temp->prev = newLink;
//	 FIXME: you must write this 
	}
	else {
		q->Sentinel->next = newLink;
		q->Sentinel->prev = newLink;
		newLink->prev = q->Sentinel;
		newLink->next = q->Sentinel;
	}
	
	q->size++;
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	assert(q && q->size != 0);
	//if (q->size != 0)
		return q->Sentinel->next->value;

	//else
	//	return 0;
	/* FIXME: you must write this */	 
	/*temporary return value..you may need to change it*/
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(q && q->size != 0);
//	if (q->size != 0)
		return q->Sentinel->prev->value;
//	else
//		return 0;
	/* FIXME: you must write this */	 
	/*temporary return value..you may need to change it*/
	
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{

	assert(q && q->size != 0);

//i dont think i need these temps
//	struct DLink *temp = lnk->next;
//	struct DLink *temp2 = lnk->prev;
//	
	lnk->prev->next = lnk->next;
	lnk->next->prev = lnk->prev;

	free(lnk);
	q->size--;
	/* FIXME: you must write this */	 

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {

	assert(q && q->size != 0);
	
	struct DLink *temp = q->Sentinel->next->next;
	
	free(q->Sentinel->next);

	q->Sentinel->next = temp;
	q->Sentinel->next->prev = q->Sentinel;

	q->size--;
	

	/* FIXME: you must write this */	 

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	assert(q && q->size != 0);

	struct DLink *temp = q->Sentinel->prev->prev;
	free(q->Sentinel->prev);

	q->Sentinel->prev = temp;
	q->Sentinel->prev->next = q->Sentinel;

	q->size--;
  	/* FIXME: you must write this */	 
}

/* De-allocate all links of the deque, and the deque itself

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	int i = 0;
	for (i = 0; i<q->size; i++)
		removeBackCirListDeque(q);

	free(q->Sentinel);
	free(q);
	/* FIXME: you must write this */	 
	
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	
	assert(q);
	
	if (q->size == 0)
		return 1;
	else
		return 0;
  	/* FIXME: you must write this */
	/*temporary return value..you may need to change it*/
	
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	
	assert(q && !isEmptyCirListDeque(q));
	struct DLink *temp = q->Sentinel->next;
	int i = 1;
	do{
		printf("Value %d: %f\n", i, temp->value);
		temp = temp->next;
		i++;
	} while(temp != q->Sentinel);

	/* FIXME: you must write this */	 

}
