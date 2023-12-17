
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to find the median of three elements
std::vector<int>::iterator medianOfThree(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator middle = low + (high - low) / 2;

    // Sorts the low, middle, and high elements of the vector
    if (*middle < *low) {
        std::iter_swap(middle, low);
    }
    if (*high < *low) {
        std::iter_swap(high, low);
    }
    if (*high < *middle) {
        std::iter_swap(high, middle);
    }
    // returns median
    return middle;
}

// Function to perform Hoare partition with median-of-three pivot selection and placement
std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator pivot = medianOfThree(nums, low, high);

    int pivotValue = *pivot;
    auto i = low;
    auto j = high;

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

// Function to perform quick select with median-of-three pivot selection and placement
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    // Using Hoare's partition with median-of-three pivot selection and placement
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
