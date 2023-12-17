#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to find the median of three elements
std::vector<int>::iterator medianOfThree(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator middle = low + (high - low) / 2;

    // Identify the median of low, middle, and high elements
    std::vector<int>::iterator median;
    if (*middle < *low && *low < *high) {
        median = low;
    } else if (*high < *low && *low < *middle) {
        median = low;
    } else if (*low < *middle && *middle < *high) {
        median = middle;
    } else if (*high < *middle && *middle < *low) {
        median = middle;
    } else {
        median = high;
    }

    // Swap the median into the "high" index
    std::iter_swap(median, high);

    return high;
}

// Function to perform Hoare partition with median-of-three pivot selection and placement
std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    // Pivot is assumed to be in the correct position already (in this case, at 'high')
    std::vector<int>::iterator pivot = high;
    int pivotValue = *pivot;

    auto i = low;
    auto j = high - 1; // Start 'j' one position before the pivot

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
            return i; // 'i' is the correct position for the pivot
        }

        std::iter_swap(i, j);

        // Increment and decrement iterators to avoid going out of bounds
        i++;
        j--;
    }
}

// Function to perform quick select with median-of-three pivot selection and placement
int quickSelect(std::vector<int>& nums, int& duration) {
    // start of clock for duration
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
