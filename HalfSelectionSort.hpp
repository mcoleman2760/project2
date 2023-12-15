#ifndef HALF_SELECTION_SORT_HPP
#define HALF_SELECTION_SORT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

template <typename Iterator>
Iterator findSmallest(Iterator begin, Iterator end) {
    Iterator smallest = begin;
    for (Iterator it = begin + 1; it != end; ++it) {
        if (*it < *smallest || (*it == *smallest && it < smallest)) {
            smallest = it;
        }
    }
    return smallest;
}

template <typename Iterator>
void swapSmallestToPosition(Iterator begin, Iterator end, size_t position) {
    Iterator smallest = findSmallest(begin, end);
    std::iter_swap(begin + position, smallest);
}

int halfSelectionSort(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    if (nums.size() > 50000) {
        std::cout << "Input is too big for half selection sort." << std::endl;
        return 0;  // Placeholder value for the median
    }

    size_t targetIndex = nums.size() / 2;

    for (auto it = nums.begin(); it != nums.begin() + targetIndex; ++it) {
        swapSmallestToPosition(it, nums.end(), std::distance(nums.begin(), it));
    }

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Return the median
    return nums[targetIndex];
}

#endif  // HALF_SELECTION_SORT_HPP
