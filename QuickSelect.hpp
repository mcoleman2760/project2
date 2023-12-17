#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to find the median of three elements
std::vector<int>::iterator medianOfThree(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto mid = low + std::distance(low, high) / 2;

    // Sort the three elements
    if (*low > *mid)
        std::iter_swap(low, mid);
    if (*mid > *high)
        std::iter_swap(mid, high);
    if (*low > *mid)
        std::iter_swap(low, mid);

    // Place the median at the end (pivot position)
    std::iter_swap(mid, high);

    return high;
}

// Hoare partition method
std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto pivotIter = high;
    int pivot = *pivotIter;
    auto i = low - 1;
    auto j = high;

    while (true) {
        do {
            ++i;
        } while (*i < pivot);

        do {
            --j;
        } while (*j > pivot && j > low);

        if (i >= j) {
            // Swap the pivot into its correct position
            std::iter_swap(i, pivotIter);
            return i;
        }

        // Swap elements to maintain the partition
        std::iter_swap(i, j);
    }
}

// QuickSelect algorithm
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    auto low = nums.begin();
    auto high = nums.end() - 1;

    while (high > low) {
        // Use quicksort for small subarrays
        if (std::distance(low, high) + 1 <= 10) {
            std::sort(low, high + 1);
            break;
        }

        // Choose pivot using median of three method
        auto pivotIter = medianOfThree(nums, low, high);

        // Call hoarePartition to place the pivot in its correct position
        auto pivotIndex = hoarePartition(nums, low, high);

        // Recur on the smaller side of the pivot
        if (pivotIndex > low)
            high = nums.begin() + pivotIndex - 1;
        else if (pivotIndex < low)
            low = nums.begin() + pivotIndex + 1;
        else
            break; // Pivot is at the correct position
    }

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return *low;
}
