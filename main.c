#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "type.h"
#include "functions.h"

int main(int argc, char *argv[])
{
        int arr[] = { 12, 11, 13, 5, 6, 7 };
        int arr_size = sizeof(arr) / sizeof(arr[0]);
        thrd_t first;

        printf("Given array is \n");
        printArray(arr, arr_size);

        inputToThread x;
        x.arr = arr;
        x.l = 0;
        x.r = arr_size - 1;
        thrd_create(&first, mergeSort, (void*) &x);
        thrd_join(first, (int*) NULL);

        printf("\nSorted array is \n");
        printArray(arr, arr_size);

        return EXIT_SUCCESS;
}
