#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to find the median of three elements
std::vector<int>::iterator medianOfThree(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator middle = low + (high - low) / 2;

    // Sort the low, middle, and high elements
    if (*middle < *low) {
        std::iter_swap(middle, low);
    }
    if (*high < *low) {
        std::iter_swap(high, low);
    }
    if (*high < *middle) {
        std::iter_swap(high, middle);
    }

    return middle;
}

// Function to perform Hoare partition with pivot placement
std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator pivot = medianOfThree(nums, low, high);
    int pivotValue = *pivot;

    // Move the pivot to the rightmost position (just before 'high')
    std::iter_swap(pivot, high - 1);
    
    auto i = low;
    auto j = high - 1;

    while (true) {
        // Move i to the right until an element greater than or equal to the pivot is found
        while (*i < pivotValue) {
            i++;
        }

        // Move j to the left until an element less than or equal to the pivot is found
        while (*j > pivotValue) {
            j--;
        }

        if (i >= j) {
            return j;
        }

        std::iter_swap(i, j);

        // Increment and decrement iterators to avoid going out of bounds
        i++;
        j--;
    }
}

// Helper function to perform quick sort when the subarray size is 10 or less
void insertionSort(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::sort(low, high + 1);
}

// Function to perform Quickselect
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int>::iterator low = nums.begin();
    std::vector<int>::iterator high = nums.end() - 1;

    while (high - low + 1 > 10) {
        std::vector<int>::iterator pivot = hoarePartition(nums, low, high);
        
        // Recurse on the smaller partition
        if (pivot - low < high - pivot) {
            quickSelect(nums, duration);
            low = pivot + 1;
        } else {
            quickSelect(nums, duration);
            high = pivot - 1;
        }
    }

    // Use insertion sort for small subarrays
    insertionSort(nums, low, high);

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return *(low + (high - low) / 2);
}
