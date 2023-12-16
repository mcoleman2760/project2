#ifndef QUICK_SELECT_HPP
#define QUICK_SELECT_HPP

#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>



template<typename Iterator>
Iterator medianOfThree(Iterator low, Iterator high) {
    Iterator mid = low + (high - low) / 2;

    // Choose the median of three as the pivot
    Iterator pivot = low;

    if (*mid < *pivot) {
        std::iter_swap(mid, pivot);
    }

    if (*high < *pivot) {
        std::iter_swap(high, pivot);
    }

    if (*mid > *high) {
        std::iter_swap(mid, high);
    }

    return mid; // Return the iterator to the chosen pivot
}

// Function to perform the Hoare partition

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::vector<int>::iterator pivot = high;

    while (true) {
        do {
            ++low;
        } while (*low < *pivot);

        do {
            --high;
        } while (*high > *pivot);

        if (low >= high) {
            return high;
        }

        std::iter_swap(low, high);
    }
}

// Helper function for pivot selection and placement
template<typename Iterator>
void selectAndPlacePivot(Iterator low, Iterator high) {
    Iterator pivot = medianOfThree(low, high);
    std::iter_swap(pivot, high);
}

// Recursive QuickSelect function
template<typename Iterator>
int quickSelectHelper(std::vector<int>& nums, Iterator low, Iterator high) {
    // Base case: if subarray size is 10 or less, use std::sort
    if (std::distance(low, high) <= 10) {
        std::sort(low, high + 1);
        return *(low + std::distance(low, high) / 2);
    }

    // Choose pivot and place it in position
    selectAndPlacePivot(nums, low, high);
    Iterator pivotIterator = hoarePartition(nums, low, high);

    // Recursive case: recurse on one side of the pivot
    if (pivotIterator > low) {
        return quickSelectHelper(nums, low, pivotIterator - 1);
    } else {
        return *pivotIterator;
    }
}

// Function to perform QuickSelect
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    int result = quickSelectHelper(nums ,nums.begin(), nums.end() - 1);

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return result;
}

#endif // QUICKSELECT_HPP
