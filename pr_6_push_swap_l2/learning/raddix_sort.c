#include <stdio.h>

#define MAX_SIZE 1000

// get max val from the arr
int getMax(int arr[], int arr_len)
{
    int max = arr[0];
    for (int i=1; i<arr_len; i++)
    {
        if (arr[i]>max)
            max = arr[i];
    }
    return max;
}

// loop through the els in the arr: store how many times each digit at curr place from the arr is
void countingSort(int arr[], const int arr_len, int exp)
{
    // lazy to use malloc, so hard code arr_max
    int output[MAX_SIZE];
    int count[10] = {0};

     // Count occurrences of each digit at the current place value (exp)
    for (int i=0; i<arr_len; i++){
        count[(arr[i]/exp)%10]++;
    }
    for (int i = 0; i < 10; i++)
        printf("%d ", count[i]);
     // Change count[i] to store the actual position of this digit in output[]
     for (int i=1; i<10; i++) {
        count[i] += count[i-1];
     }
    printf("\n");
     for (int i = 0; i < 10; i++)
        printf("%d ", count[i]);

    for (int i = arr_len - 1; i >= 0; i--) {
        int index = (arr[i]/exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
     printf("\n");
     int length = sizeof(arr) / sizeof(arr[0]);
     for (int i = 0; i < length; i++)
        printf("%d ", output[i]);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]); // arr.length
    printf("Original array: \n");
    printArray(arr, n);

    countingSort(arr, n, 1);
    // printf("Sorted array: \n");
    // printArray(arr, n);
    return 0;
}