/**
 * EE 312, 2021 Fall, Recitation 2
 * Name: Anvit Raju
 * UT EID: ar68234
 */
#include <stdio.h>
#include <stdlib.h>

// Returns an array containing [n, n+1, ..., m-1, m].
// Requirements:
// 1. If n > m, then the array returned is [].
// 2. If an error occurs, NULL is returned
int* RangeArray(int n, int m) {
  int length = m - n + 1;

  // heap-allocated the array needed to return
  int *array = (int*)malloc(sizeof(int) * length);

  // initialize the elements
  int i=0;
  for (i; i < length; ++i) {
    array[i] = i + n;
  }

  return array;
}

int main(void) {
  int start;
  int end;

  // Accepts two integers as arguments
  printf("This Program will create the array: [start ... end]\n");
  printf("Please Input your Start Number: ");
  scanf("%d", &start);
  printf("Please Input your End Number: ");
  scanf("%d", &end);

  // print the resulting array
  int *nums = RangeArray(start, end);
  int i=0;
  for (i; i < (end-start+1); ++i) {
    printf("%d ", nums[i]);
  }

  free(nums);

  puts(" ");
  return 0;
}
