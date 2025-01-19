#include <stdio.h>

/**
 *     O(1) complexity
*/
char get_element(char arr[], int index) {
    return arr[index]; // Always takes constant time, O(1)
}

/**
 * O(log n): Logarithmic Time
Time complexity grows slowly, usually by halving the input at each step. Example: Binary Search ( works only on sorted arrays)
*/
int binary_search(char arr[], int size, char target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

/**
 * O(n): Linear Time. Quick sort
*/
int linear_search(char arr[], int size, char target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

/**
 * O(n log n): Log-linear Time
 * Example: Quck Sort uses a divide-and-conquer strategy, splitting the arr into smaller segments
*/
int partition(char arr[], int low, int high) {
    char end_el = arr[high];
    int i = low - 1;
    for (int lo = low; lo < high; lo++) {
        if (arr[lo] < end_el) {
            i++;
            char temp = arr[i];
            arr[i] = arr[lo];
            arr[lo]= temp;
        }
    }
    char temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high]= temp;
    return (i + 1);
}

void quick_sort(char arr[], int low, int high) {
    if (low < high) {
        int some_index = partition(arr, low, high);
        quick_sort(arr, low, some_index - 1);
        quick_sort(arr, some_index + 1, high);
    }
}

/**
 * O(n2): Quadratic Time: time complexity grows quadratically with the input size, often involving nested loops: In Bubble Sort, each element is compared with every other element, resulting in O(n²) complexity. This makes it inefficient for large inputs.
 * 
*/
void bubble_sort(char arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    char arr22[9] = {'3', '8', '2', '5', '1', '4', '7', '6'};
    quick_sort(arr22, 0, 4);

    bubble_sort(arr22, 7);
    char arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    int ind = binary_search(arr, 10, 'f');
    printf("binary search: %c\n",arr[ind]);
    return 0;
}
