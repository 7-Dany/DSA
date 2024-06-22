#ifndef _SORTING_H_
#define _SORTING_H_

#include <stdint.h>

#define swap(one, two, type) \
  do {                       \
    type temp = (one);       \
    (one) = (two);           \
    (two) = (temp);          \
  } while (0)

#define print_arr(arr, len, format)       \
  do {                                    \
    printf("[");                          \
    for (int i = 0; i < (len); i++) {     \
        printf(format, (arr)[i]);         \
        if (i < (len) - 1) printf(", ");  \
    }                                     \
    printf("]\n");                        \
  } while (0)

void shuffle_array(int *array, int len, uint32_t delay);
void insertion_sort(int *array, int len, uint32_t delay); 
void bubble_sort(int *array, int len, uint32_t delay);
void bogo_sort(int *array, int len, uint32_t delay);
void selection_sort(int *array, int len, uint32_t delay);
void merge_sort(int *array, int len, uint32_t delay);
void quick_sort(int *array, int len, uint32_t delay); 
void radix_sort(int *array, int len, uint32_t delay); 

#endif // _SORTING_H_

