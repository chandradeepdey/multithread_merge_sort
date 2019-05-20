#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "type.h"
#include "functions.h"

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
int mergeSort(void *input)
{
        int (*msort)(void *) = mergeSort;
        thrd_t first, second;
        inputToThread * x = (inputToThread *) input;

        if (x->l < x->r) {
                // Same as (l+r)/2, but avoids overflow for
                // large l and h
                int m = x->l + (x->r - x->l) / 2;

                inputToThread l;
                l.arr = x->arr;
                l.l = x->l;
                l.r = m;
                // Sort first and second halves
                thrd_create(&first, msort, (void *) &l);

                inputToThread r;
                r.l = m + 1;
                r.r = x->r;
                thrd_create(&second, msort, (void *) &r);

                thrd_join(first, (int *) NULL);
                thrd_join(second, (int *) NULL);
                merge(x->arr, x->l, m, x->r);
        }

        thrd_exit(EXIT_SUCCESS);
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        /* create temp arrays */
        int L[n1], R[n2];

        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
                L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
                R[j] = arr[m + 1 + j];

        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray
        j = 0; // Initial index of second subarray
        k = l; // Initial index of merged subarray
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

        /* Copy the remaining elements of L[], if there
         are any */
        while (i < n1) {
                arr[k] = L[i];
                i++;
                k++;
        }

        /* Copy the remaining elements of R[], if there
         are any */
        while (j < n2) {
                arr[k] = R[j];
                j++;
                k++;
        }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
        int i;
        for (i = 0; i < size; i++)
                printf("%d ", A[i]);
        printf("\n");
}
