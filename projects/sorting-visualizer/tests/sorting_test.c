#include "../src/sorting.h"
#include <stdio.h>

#define ARR_LEN 15

const int ARR[ARR_LEN] = {
    90, -4, 6289, 0, 6, 
    100, 3, 32002, -10, 560,
    1, 2, 5, 300, 7,
};

void create_arr(int *arr)
{
    for (int i = 0; i < ARR_LEN; i++) {
        arr[i] = ARR[i];
    }
}

int main(void)
{
    int arr[ARR_LEN];

    create_arr(arr);
    printf("Initial Array:\n");
    print_arr(arr, ARR_LEN, "%d");

    printf("Insertion Sort:\n");
    insertion_sort(arr, ARR_LEN); 
    print_arr(arr, ARR_LEN, "%d");

    printf("Bubble Sort:\n");
    create_arr(arr);
    bubble_sort(arr, ARR_LEN);
    print_arr(arr, ARR_LEN, "%d");

    /* Too slow 
    printf("Bogo Sort:\n");
    create_arr(arr);
    bogo_sort(arr, ARR_LEN);
    print_arr(arr, ARR_LEN, "%d");
    */

    printf("Selection Sort:\n");
    create_arr(arr);
    selection_sort(arr, ARR_LEN);
    print_arr(arr, ARR_LEN, "%d");

    printf("Merge Sort:\n");
    create_arr(arr);
    merge_sort(arr, ARR_LEN);
    print_arr(arr, ARR_LEN, "%d");

    printf("Quick Sort:\n");
    create_arr(arr);
    quick_sort(arr, ARR_LEN);
    print_arr(arr, ARR_LEN, "%d");

    printf("Radix Sort:\n");
    create_arr(arr);
    radix_sort(arr, ARR_LEN); 
    print_arr(arr, ARR_LEN, "%d");

    return 0;
}
