/**
 *      author  : Frenaldy
 *      crreated: 19.04.2025
**/

#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// Quicksort
int partition(int arr[], int l, int r) { // Zero indexed
    int pivot = arr[r];

    int i, j;
    for(j = i = l; j < r; j++) {
        if(arr[j] < pivot) {
            swap(&arr[i], &arr[j]); i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

void quicksort(int arr[], int l, int r) {
    if(l < r) {
        int mid = partition(arr, l, r);

        quicksort(arr, l, mid - 1);
        quicksort(arr, mid + 1, r);
    }
}

void fill_binary_search_tree(int arr[], int bst[], int l, int r, int idx) {
    if(l > r) return;

    int mid = (l + r) / 2;
    bst[idx] = arr[mid];

    fill_binary_search_tree(arr, bst, l, mid - 1, idx * 2);
    fill_binary_search_tree(arr, bst, mid + 1, r, idx * 2 + 1);
}

int main() {
    int arr[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int size_arr = sizeof(arr) / sizeof(int);
    quicksort(arr, 0, size_arr - 1);

    int bst[size_arr + 1];
    fill_binary_search_tree(arr, bst, 0, size_arr - 1, 1);

    printf("Complete Binary Search Tree representation:\n");
    for(int i = 1; i <= size_arr; i++) 
        printf("%d ", bst[i]);
    printf("\n");
}