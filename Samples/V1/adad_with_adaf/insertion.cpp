#include <stdlib.h>
#include "adad.h"
#include "adaf.h"

int a_insertionSort(adaf_array arr, adad n) {
  adad i, j;
  adaf key;
  for (i = 1; i < n; i++) {	// Iterate from the second element
    key = arr[i];		// Store the current element to be inserted
    j = i - 1;			// Initialize j to the index of the element before 'key'
				// Move elements of arr[0..i-1], that are greater than 'key',
				// to one position ahead of their current position
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];	// Shift element to the right
      j = j - 1;		// Move to the previous element
    }
    arr[j + 1] = key;		// Place the 'key' at its correct sorted position
  }
  return 0;
}

int pain(int size) {
  float      *input;
  int         i;

  input = new float[size];
  for (i=0; i<size; i++) {
    input[i] = random() * 4.656612e-10f - 0.5f;
  }
  printf("made float array %d long\n", size);

  adad        asize;
  adaf_array  arr(input, size);
  asize = size;

  printf("converted float array to adaf\n");

  a_insertionSort(arr, asize);

  printf("performed the quick sort\n");

  // copy the sorted array back
  for (i=0; i<size; i++) {
    input[i] = arr[i].val();
  }

  // check the sorting
  for (i=1; i<size; i++) {
    if (input[i-1] > input[i]) {
      printf("A[%d]=%f and A[%d]=%f ?\n", i-1, input[i-1], i, input[i]);
      printf("sort was not OK\n");
      return 1;
    }
  }

  printf("sort was OK\n");

  return 0;
}
