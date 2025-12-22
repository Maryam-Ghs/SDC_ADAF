#include <stdlib.h>
#include "adad.h"
#include "adaf.h"

int a_heapify(adaf_array arr, adad N, adad i) {
  adad largest, left, right, tmp2, tmp3;
  adaf temp;

  largest = i;
  tmp2 = 2*i;
  left = tmp2+1;
  tmp3 = 2*i;
  right = tmp3+2;
  if ((left<N) &&
      (arr[left]>arr[largest])) {
    largest = left;
  }
  if ((right<N) &&
      (arr[right]>arr[largest])) {
    largest = right;
  }
  if (largest != i) {
    temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    a_heapify(arr, N, largest);
  }
  return 0;
}

int a_heapSort(adaf_array arr, adad N, adad low, adad high) {
  adad	i, tmp2;
  adaf  temp;
  tmp2 = N/ 2;
  i = tmp2-1;
  while (i>=0) {
    a_heapify(arr, N, i);
    i -= 1;
  }
  i = N-1;
  while (i>=0) {
    temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    a_heapify(arr, i, 0);
    i -= 1;
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

  adad        asize, alow, ahigh;
  adaf_array  arr(input, size);
  asize = size;

  printf("converted float array to adaf\n");

  alow = 0;
  ahigh = size;
  a_heapSort(arr, asize, alow, ahigh);

  printf("performed the heap sort\n");

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
