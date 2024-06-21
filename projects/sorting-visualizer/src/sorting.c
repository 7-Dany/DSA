#include "sorting.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

void shuffle_array(int *array, int len)
{
    int i, j;
    SetRandomSeed(time(0));

    for (i = 0; i < len - 1; i++) {
        j = GetRandomValue(i + 1, len - 1);
        swap(array[i], array[j], int);
    }
}

void insertion_sort(int *array, int len) 
{
    for (int i = 1; i < len; i++) {
        int temp = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = temp;
    }
}

void bubble_sort(int *array, int len) 
{
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

bool is_sorted(int *array, int len) 
{
    for (int i = 0; i < len - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }

    return true;
}

void bogo_sort(int *array, int len) 
{
    while (! is_sorted(array, len)) {
        shuffle_array(array, len);
    }
}

void selection_sort(int *array, int len) 
{
    for (int i = 0; i < len; i++) {
        int min = i;

        for (int j = i; j < len; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }

        swap(array[min], array[i], int);
    }
}

void merge(int *array, int l1, int r1, int l2, int r2)
{
    int i = l1;
    int j = l2;
    int k = 0;
    int result_len = (r2 - l1) + 1;
    int *results = (int*)malloc(result_len * sizeof(int));

    while (i < r1 + 1 && j < r2 + 1) {
        if (array[i] < array[j]) {
            results[k] = array[i];
            i++;
            k++;
        }  
        else {
            results[k] = array[j];
            j++;
            k++;
        }
    }

    while (i < r1 + 1) {
        results[k] = array[i];
        i++;
        k++;
    }

    while (j < r2 + 1) {
        results[k] = array[j];
        j++;
        k++;
    }

    k = 0;

    for (int x = l1; x < r2 + 1; x++) {
        array[x] = results[k];
        k++;
    }

    free(results);
}

void MERGE_SORT(int *array, int l, int r)
{
    if (r - l == 0) return;

    int mid = floor((l + r) / 2.f);
    int left1 = l;
    int right1 = mid;
    int left2 = mid + 1;
    int right2 = r;

    MERGE_SORT(array, left1, right1);
    MERGE_SORT(array, left2, right2);

    merge(array, left1, right1, left2, right2);
}

void merge_sort(int *array, int len) 
{
    MERGE_SORT(array, 0, len - 1);
}

int partition(int *array, int start, int end) 
{
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j] < array[end]) {
            i++;
            swap(array[i], array[j], int);
        }
    }

    i++;
    swap(array[i], array[end], int);

    return i;
}

void QUICK_SORT(int *array, int start, int end)
{
    if (start > end) return;
    int pivot = partition(array, start, end);
    QUICK_SORT(array, start, pivot - 1);
    QUICK_SORT(array, pivot + 1, end);
}

void quick_sort(int *array, int len) 
{
    QUICK_SORT(array, 0, len - 1);
}

int get_digit(int number, int index) 
{
    return (int)(number / pow(10, index)) % 10;
}

void counting(int *array, int *output, int len, int index) 
{
    int counts[10] = {0};
    for (int i = 0; i < len; i++) {
        int d = get_digit(array[i], index);
        counts[d] += 1;
    }

    for (int i = 1; i < 10; i++) {
        counts[i] += counts[i - 1];
    }

    for (int i = len - 1; i >= 0; i--) {
        int d = get_digit(array[i], index);
        int j = counts[d] - 1;
        counts[d] -= 1;
        output[j] = array[i];
    }
}

void radix_sort(int *array, int len) 
{
    int maxNumber = INT32_MIN;
    int minNumber = INT32_MAX;

    for (int i = 0; i < len; i++) {
        if (array[i] > maxNumber) maxNumber = array[i];
        if (array[i] < minNumber) minNumber = array[i];
    }
    
    if (minNumber < 0) {
        for (int i = 0; i < len; i++) {
            array[i] += minNumber * -1;
        }
    }

    int digits = floor(log10(maxNumber)) + 1;

    int *output = (int*)malloc(len * sizeof(int));

    int *input_ptr = array;
    int *output_ptr = output;

    for (int i = 0; i < digits; i++) {
        counting(array, output, len, i);
        swap(array, output, int*);
    }
    
    if (array != input_ptr) {
        swap(array, output, int*);
        for (int i = 0; i < len; i++) {
            array[i] = output[i];
        }
    }

    if (minNumber < 0) {
        for (int i = 0; i < len; i++) {
            array[i] += minNumber;
        }
    }

    free(output_ptr);
}
