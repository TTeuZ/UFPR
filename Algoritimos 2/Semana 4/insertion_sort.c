// //Organização por inserção;

#include <stdio.h>
// int *insection_sort(int v[], int a, int b);
// int *insert(int v[], int a, int b);
// int find(int x,int v[], int a, int b);

// void main(int argc, char *argv[]) {
//     int v[10] = {20, 32, 31, 10, 6, 9};
//     int *v_sorted = insection_sort(v, 0, 5);
//     for (int i = 0; i <= 5; i++) {
//         printf("%d\n", v_sorted[i]);
//     }
// }

// int *insection_sort(int v[], int a, int b) {
//     if (a > b) return v;
//     insection_sort(v, a, b-1);
//     v = insert(v, a, b);
//     return v;
// }
// int *insert(int v[], int a, int b) {
//     int p = find(v[b], v, a, b-1);
//     printf("Posição encontrada de B: %d\n", p);
//     int i = b;
//     while (i >= p + 1) {
//         int x = v[a];
//         v[a] = v[b];
//         v[b] = x;
//         i = i - 1;
//     }
//     return v;
// }
// int find(int x,int v[], int a, int b) {
//     if (a > b) return a-1;
//     if (x >= v[b]) return b;
//     return find(x, v, a, b-1);
// }

// Recursive function to sort an array using
// insertion sort
void insertionSortRecursive(int arr[], int n)
{
    // Base case
    if (n <= 1)
        return;
 
    // Sort first n-1 elements
    insertionSortRecursive( arr, n-1 );
 
    // Insert last element at its correct position
    // in sorted array.
    int last = arr[n-1];
    int j = n-2;
 
    /* Move elements of arr[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}
 
// A utility function to print an array of size n
void printArray(int arr[], int n)
{
    for (int i=0; i < n; i++)
        printf("%d ", arr[i]); 
    printf("\n");
}
 
/* Driver program to test insertion sort */
int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    insertionSortRecursive(arr, n);
    printArray(arr, n);
 
    return 0;
}

// Algoritimo funcional porem copiado da net