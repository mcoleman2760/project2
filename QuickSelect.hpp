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

// Function to select and place pivot using the median-of-three method
std::vector<int>::iterator selectAndPlacePivot(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator pivot = medianOfThree(nums, low, high);

    // Move the pivot to the rightmost position (just before 'high')
    std::iter_swap(pivot, high - 1);
    
    return high - 1; // Return the iterator to the pivot
}

// Function to perform Hoare partition with pivot selection and placement
std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator pivot = selectAndPlacePivot(nums, low, high);
    int pivotValue = *pivot;
    auto i = low - 1;
    auto j = high;

    while (true) {
        do {
            i++;
        } while (*i < pivotValue);

        do {
            j--;
        } while (*j > pivotValue);

        if (i >= j) {
            return j;
        }

        std::iter_swap(i, j);
    }
}

// Function to perform quick select with pivot selection and placement
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    // Using Hoare's partition with pivot selection and placement
    std::vector<int>::iterator low = nums.begin();
    std::vector<int>::iterator high = nums.end() - 1;
    int k = nums.size() / 2; // Change k to the desired position (e.g., median)

    while (low <= high) {
        std::vector<int>::iterator pivot = hoarePartition(nums, low, high);

        if (pivot == nums.begin() + k) {
            break; // Found the element at the k-th position
        } else if (pivot < nums.begin() + k) {
            low = pivot + 1;
        } else {
            high = pivot - 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return *(nums.begin() + k);
}
