#include <stdio.h>
#include <stdlib.h>

// This copies the contents of fromArray into toArray
void arrayCopy(int fromArray[], int toArray[], int size) {
    for(int i = 0; i < size; i++) toArray[i] = fromArray[i];
}

/* Helper function to merge two halves of an array in sorted order
 * @param arr           => array to sort
 * @param leftHalfStart => begining of left half of array
 * @param rightHalfEnd  => end of right half of array
 * @param result        => array to hold numbers when they are sorted
 */
void merge(int arr[], int leftHalfStart, int rightHalfEnd, int result[]) {
    // Find the boundaries of each half that we are missing
    int leftHalfEnd = (leftHalfStart + rightHalfEnd) / 2;
    int rightHalfStart = leftHalfEnd + 1;
    int size = rightHalfEnd - leftHalfStart + 1;
    // Set up vars for tracking progress through the array
    int left = leftHalfStart;
    int right = rightHalfStart;
    int sortedIndex = leftHalfStart;
    // Check for the lesser of the two numbers between left and right halves
    // and apply it to @param result
    while(left <= leftHalfEnd && right <= rightHalfEnd) {
        if(arr[left] <= arr[right]) {
            result[sortedIndex] = arr[left];
            left++;
        } else {
            result[sortedIndex] = arr[right];
            right++;
        }
        sortedIndex++;
    }
    // If there are any #'s remaining in the left half, add them to result
    while(left <= leftHalfEnd) {
        result[sortedIndex] = arr[left];
        sortedIndex++;
        left++;
    }
    // If there are any #'s remaining in the right half, add them to result
    while(right <= rightHalfEnd) {
        result[sortedIndex] = arr[right];
        sortedIndex++;
        right++;
    }
    // Finally, copy the sorted result into the original array
    arrayCopy(result, arr, sortedIndex);
}

// My implementation of a merge sort using recursion
void mergeSort(int arr[], int left, int right, int result[]) {
    if(left >= right) return;
    int mid = (left + right) / 2;            // Find middle btwn. left and right side
    mergeSort(arr, left, mid, result);       // Merge sort left side
    mergeSort(arr, mid + 1, right, result);  // Merge sort right side
    merge(arr, left, right, result);         // Merge left and right side
}

// Merge sort wrapper for syntactically sugary usage 
// Note: this function manipulates the original array!
void sort(int arr[], int size) {
    int result[size];
    mergeSort(arr, 0, size - 1, result);
}

/* Use linear search to look up number in unsorted array
 * @param arr => array of unsorted numbers
 * @param size => number of elements in arr
 * @param target => number we want to find
 * @param numComparisons => counter for number of comparisons binSearch makes
 * @return => index of target if found, -1 otherwise
 */
int linSearch(int arr[], int size, int target, int* numComparisons) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == target) {
            (*numComparisons)++;
            return i;
        }
        (*numComparisons)++;
    }
    return -1;
}

/* Use binary search to look up number in sorted array
 * @param arr => array of sorted numbers
 * @param size => number of elements in arr
 * @param target => number we want to find
 * @param numComparisons => counter for number of comparisons binSearch makes
 * @return => index of target if found, -1 otherwise
 */
int binSearch(int arr[], int size, int target, int* numComparisons) {
    int low, mid, high, searchResult = -1;  
    // Binary search for word
    low = 0, high = size - 1;
    // If there is a spread between the low and high, continue halfing,
    // Until the number is found
    while ( low <= high)  {
        mid = (low + high) / 2; // Compute the middle
        if (target == arr[mid]) {       // Number FOUND!
            (*numComparisons)++;
            return mid;
        } else if (target < arr[mid]) { // Number is before middle location
            (*numComparisons) += 2;
            high = mid - 1;
        } else {                        // Number is after middle location
            (*numComparisons) += 2;
            low = mid + 1;
        }
    }
    // Word NOT FOUND!
    return -1;
}

int* doubleArraySize(int* darr, int* size) {
     // Make new array double the current size
    int *tmp = (int*)malloc((*size) * 2 * sizeof(int));
    // Copy old array elements to new array
    for (int i = 0; i < (*size); i++)
        tmp[i] = darr[i];
    // Free old array memory, then reset array and it's new size
    free(darr);
    (*size) *= 2;
    return tmp;
}

void checkIfNumFound(int indexFound, int numComparisons) {
    (indexFound < 0) ? 
        printf("\tNumber was not found after %d comparisons\n\n", numComparisons) : 
        printf("\tNumber was found after %d comparisons at index %d\n\n", 
               numComparisons,
               indexFound
        );
}

int main() {
    int userEntry, numsEntered = 0, numComparisons = 0, indexFound = 0;

    int* numStorage;
    int size = 2;  // This is the initial size of the array
    numStorage = (int *)malloc(size * sizeof(int));

    printf("\nPlease enter as many integers as you would like in your array!\n\n");
    printf("When you are finished, enter the integer `-999` to stop.\n\n");

    printf(">> ");
    scanf("%d", &userEntry);

    while(userEntry != -999) {
        if(numsEntered >= size)
            numStorage = doubleArraySize(numStorage, &size);
        numStorage[numsEntered] = userEntry;
        numsEntered++;
        scanf("%d", &userEntry);
    }

    // Making a copy of numStorage to sort, leaving the original unsorted
    int* numStorageCopy = (int*)malloc(numsEntered * sizeof(int));
    arrayCopy(numStorage, numStorageCopy, numsEntered);

    sort(numStorageCopy, numsEntered);

    // 37 82 92 99 39 0 10 25 15 16 19 98 76 -999

    printf("\nPlease enter as many integers as you would like to search for in the array!\n\n");
    printf("When you are finished, enter the integer `-999` to stop.\n\n");

    printf(">> ");
    scanf("%d", &userEntry);

    while(userEntry != -999) {
        numComparisons = 0;
        indexFound = linSearch(numStorage, numsEntered, userEntry, &numComparisons);
        printf("\nLinear Search of unsorted array:\n");
        checkIfNumFound(indexFound, numComparisons);
        numComparisons = 0;
        indexFound = binSearch(numStorageCopy, numsEntered, userEntry, &numComparisons);
        printf("Binary Search of sorted array:\n");
        checkIfNumFound(indexFound, numComparisons);
        printf(">> ");
        scanf("%d", &userEntry);
    }

    printf("\n");

    // Clean any leftover memory currently alloc'd on the heap
    free(numStorage);
    free(numStorageCopy);

    return 0;
}