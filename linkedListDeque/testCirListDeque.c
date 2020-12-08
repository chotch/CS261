#include "cirListDeque.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
        
	struct cirListDeque *list = createCirListDeque();
	
	printf("Testing isEmpty (1 for empty 0 for otherwise. Should be 1: %d\n", isEmptyCirListDeque(list));

	printf("Adding 6 numbers to back of list \n");

	addBackCirListDeque(list, 10.392847);
	addBackCirListDeque(list, 12);
	addBackCirListDeque(list, 1532);
	addBackCirListDeque(list, 17.35);
	addBackCirListDeque(list, 31);
	addBackCirListDeque(list, 32800);

	printf("Printing list:\n ");
	printCirListDeque(list);


	printf("Adding 4 numbers to the front of list \n");
	
	addFrontCirListDeque(list, 4);
	addFrontCirListDeque(list, 81);
	addFrontCirListDeque(list, 9);
	addFrontCirListDeque(list, 20.281);

	printf("Printing list: \n");
	printCirListDeque(list);


	printf("Testing isEmpty. Should be 0: %d\n", isEmptyCirListDeque(list));


	printf("Testing frontCirListDeque: Here is the val of front of List: %f\n", frontCirListDeque(list));

	printf("Testing backCirListDeque: Here is val of back of List: %f\n", backCirListDeque(list));

	printf("Printing list: ");
	printCirListDeque(list);

	//testing addLink after
	printf("Testing _addLinkAfter to add a 5000 after the 3rd element\n");
	_addLinkAfter(list, list->Sentinel->next->next->next, 5000);
	
	printf("Printing list: \n");
	printCirListDeque(list);

	//test _removeLink
	//
	printf("Testing removeFront to remove 3 elements: \n");
	removeFrontCirListDeque(list);
	removeFrontCirListDeque(list);
	removeFrontCirListDeque(list);

	printf("Printing list: \n");
	printCirListDeque(list);

	printf("Testing removeLink to remove the 2nd element of the deque: \n");
	_removeLink(list, list->Sentinel->next->next);

	printf("Printing list: \n");
	printCirListDeque(list);


	printf("Testing removeBack: to remove 2 elements: \n");
	removeBackCirListDeque(list);
	removeBackCirListDeque(list);

	

	printf("Printing list: \n");
	printCirListDeque(list);

	printf("Freeing entire deque: \n");
	freeCirListDeque(list);



//	_addLinkAfter(list,list->Sentinel, 5);	
	/* Test your linked list in here! */
	/* Try to write the tests yourself */

	
	printf("Hello from test code!\n");
	return 0;
}


