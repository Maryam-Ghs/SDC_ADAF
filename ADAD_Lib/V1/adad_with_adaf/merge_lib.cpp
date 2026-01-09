#include <stdlib.h>
#include "adad.h"
#include "adaf.h"
#include "FI_Lib.h"

#include <stdio.h>
#include <stdlib.h> // For malloc and free

// Function to merge two sorted sub-arrays
void merge(adaf_array arr, adad left, adad mid, adad right) {
  adad i, j, k;
  adad n1 = mid - left + 1; // Size of the left sub-array
  adad n2 = right - mid;    // Size of the right sub-array

  // Create temporary arrays
  adaf_array L = adaf_array(n1.val());
  adaf_array R = adaf_array(n2.val());

  // Copy data to temporary arrays L[] and R[]
  for (i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  // Merge the temporary arrays back into arr[left..right]
  i = 0; // Initial index of first sub-array
  j = 0; // Initial index of second sub-array
  k = left; // Initial index of merged sub-array

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of L[], if any
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copy the remaining elements of R[], if any
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

// Function to perform Merge Sort
void a_mergeSort(adaf_array arr, adad left, adad right) {
  if (left < right) {
    // Find the middle point
    adad mid = left + (right - left) / 2;

    // Recursively sort first and second halves
    a_mergeSort(arr, left, mid);
    a_mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
  }
}

int main() {
  int size=100;
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
  ahigh = size-1;
  a_mergeSort(arr, alow, ahigh);

  printf("performed the merge sort\n");

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
