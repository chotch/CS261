#include <stdio.h>
#include <assert.h>

#include "pq.h"

int main(int argc, char** argv) {

  struct pq* pq = pq_create();
  int nums[16] = { 16, 8, 24, 64, 12, 4, 32, 2, 48, 80, 88, 20, 40, 6, 72, 96 };
  int min_so_far = 1000000;
  int prev = 0;

  for (int i = 0; i < 16; i++) {
    printf("== Inserting %d...", nums[i]);
    fflush(stdout);
    pq_insert(pq, &nums[i], nums[i]);
	//printf("%d", nums[i]);
    if (nums[i] < min_so_far) {
      min_so_far = nums[i];
    }
    int* first = pq_first(pq);
    assert(*first == min_so_far);
    printf(" SUCCEEDED!\n");
  }

//	printf("RIGHT HERE -CHRISTIEN");


  for (int i = 0; i < 16; i++) {
	//printf("before pq_first");
    int* first = pq_first(pq);
//	printf("before pq_remove_first");
    int* removed_first = pq_remove_first(pq);
	//printf("after pq_remove_first\n");
    printf("== Removing %d...", *removed_first);
    fflush(stdout);
    assert(*first == *removed_first);
    assert(*first > prev);
    prev = *first;
    printf(" SUCCEEDED!\n");
  }

  printf("== All tests passed!\n");

}
