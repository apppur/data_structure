#include <iostream>

#include "quicksort.h"

static void swap(int array[], int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

static int partition(int array[], int low, int hight) {
    int i = low;
    int base = array[hight];
    for (int j = low; j <= hight - 1; j++) {
        if (array[j] <= base) {
            swap(array, i, j);
            i++;
        }
    }
    swap(array, i, hight);

    return i;
}

void quicksort(int array[], int low, int hight) {
    if (low < hight) {
        int middle = partition(array, low, hight);
        quicksort(array, low, middle - 1);
        quicksort(array, middle + 1, hight);
    }
}

