/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not modify this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) == 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 */
void pq_insert(struct pq* pq, void* item, int priority) {
  assert(pq);

//	printf("value of parameter: %d\n", priority);
	int lastIndex = dynarray_size(pq->heap);
	int parentIndex = 0;
	int condition = 1;
	
//	printf("value of parameter: %d\n", priority);
	//struct pq_elem * myItem;
	struct pq_elem * myItem = malloc(sizeof(struct pq_elem*));
	myItem->item = item;
	myItem->priority = priority;

	//printf("size before insert: %d\n", dynarray_size(pq->heap)); 
	dynarray_insert(pq->heap, lastIndex, myItem);
	
//	dynarray_insert(pq->heap, lastIndex, myItem->item);
	//printf("size after insert: %d\n", dynarray_size(pq->heap)); 
	if(dynarray_size(pq->heap) == 1){
//		free(myItem);
		return;
	}
	
	parentIndex = ((lastIndex - 1) / 2);
	//printf("parent index: %d\n\n", parentIndex);

//	printf("value of priority in pg_elem struct: %d\n\n", myItem->priority);	


	while(condition){//value of item priority is less than parent, swap parent and item priority
		//printf("inside while loop");
		struct pq_elem *  newInsert = (struct pq_elem *) dynarray_get(pq->heap, lastIndex);
		struct pq_elem * firstParent = (struct pq_elem *) dynarray_get(pq->heap, parentIndex);
		//printf("New insert priority: %d\n\n", newInsert->priority);
		//printf("firstPartent priority: %d\n\n", firstParent->priority);
		if (newInsert->priority < firstParent->priority){
	
		//	dynarray_set(pq->heap, parentIndex, newInsert->item);
		//	dynarray_set(pq->heap, lastIndex, firstParent->item);
			dynarray_set(pq->heap, parentIndex, newInsert);
			dynarray_set(pq->heap, lastIndex, firstParent);
			lastIndex = parentIndex;
			parentIndex = ((lastIndex - 1)/2);
		}
		else{
//			free(myItem);
			return;
		}
	}

	
  /* FIXME: Complete this function */
  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the newly added element up in the heap array.  To
   * perform the percolation, you will have to compare the priority values of
   * the struct pq_elems in the heap array (i.e. by comparing the
   * elem->priority values).
   */

}


/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);
	struct pq_elem * highPriority = (struct pq_elem *) dynarray_get(pq->heap, 0);
	return highPriority;
  /* FIXME: Complete this function */
}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);
	int condition = 1;	
	int currentIndex = 0; //root of tree
	struct pq_elem * highPriority = (struct pq_elem *) dynarray_get(pq->heap, 0);
	
	//struct pq_elem * lastElement = (struct pq_elem *) dynarray_get(pq->heap, -1);
	struct pq_elem * lastElement = (struct pq_elem *) dynarray_get(pq->heap, dynarray_size(pq->heap) - 1);
	//assert(highPriority);
	dynarray_set(pq->heap, 0, lastElement); //set first item to equal last item
//	printf("size before removal: %d\n\n", dynarray_size(pq->heap));
	dynarray_remove(pq->heap, dynarray_size(pq->heap) - 1); //remove last element
	
//	printf("size == %d\n\n", dynarray_size(pq->heap));
//	strct pq_elem*test = (struct pq_elem*) dynarray_get(pq->heap, 14);

	if (dynarray_size(pq->heap) == 2){
		
		struct pq_elem * leftChild = (struct pq_elem *) dynarray_get(pq->heap, 2*currentIndex + 1);
	
		if (leftChild->priority < lastElement->priority){
			dynarray_set(pq->heap, 2*currentIndex + 1, lastElement);
			currentIndex = 2*currentIndex + 1;
			dynarray_set(pq->heap, (currentIndex-1)/2, leftChild);
		}

		return highPriority;
	}
	
	while(condition && dynarray_size(pq->heap) > 2){
		struct pq_elem * leftChild = (struct pq_elem *) dynarray_get(pq->heap, 2*currentIndex + 1);
		struct pq_elem * rightChild = (struct pq_elem *) dynarray_get(pq->heap, 2*currentIndex + 2);	
		
//		printf("after assigning left and right child\n\n");	
		if (leftChild->priority <= rightChild->priority && leftChild->priority < lastElement->priority){
			dynarray_set(pq->heap, 2*currentIndex + 1, lastElement);
			currentIndex = 2*currentIndex + 1;
			if (currentIndex == 1)
				dynarray_set(pq->heap, 0, leftChild);	
			else
				dynarray_set(pq->heap, (currentIndex - 1)/2, leftChild);
		//	currentIndex = 2*currentIndex + 1;

		}
		
		else if (rightChild->priority <= leftChild->priority && rightChild->priority < lastElement->priority){
			dynarray_set(pq->heap, 2*currentIndex + 2, lastElement);
			currentIndex = 2*currentIndex + 2;
			if (currentIndex == 1)
				dynarray_set(pq->heap, 0, rightChild);
			else
				dynarray_set(pq->heap, (currentIndex-1)/2, rightChild);
			//currentIndex = 2*currentIndex + 2;
		}	

		else if (rightChild->priority >= lastElement->priority && leftChild->priority >= lastElement->priority)
			return highPriority;

		if ((dynarray_size(pq->heap) - 1) / 2 <= currentIndex)
			return highPriority; 
	}
	
	return highPriority;
  /* FIXME: Complete this function */
  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */

  /*
   * Replace the highest-priority element with the appropriate one from within
   * the heap array.  Remove that replacement element from the array after
   * copying its value to the location of the old highest-priority element..
   */

  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the element that replaced the highest-priority
   * element down in the heap array.  To perform the percolation, you will
   * have to compare the priority values of the struct pq_elems in the heap
   * array (i.e. by comparing the elem->priority values).  It may be helpful
   * to write a helper function to accomplish this percolation down.
   */

  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */
}
