#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "QuickSelect.hpp"

int findMedianOfFive(std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::sort(low, high);
    return *(low + (high - low - 1) / 2);
}


// Recursive function to find the median of medians
int medianOfMedians(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int n = high - low;
    if (n <= 5) {
        // If the number of elements is small, just sort and find the median
        std::sort(low, high);
        return *(low + n / 2);
    }

    // Find the median of each group of 5 elements
    std::vector<int>::iterator groupMedian = hoarePartition(nums, low, high);

    // Recursively find the median of medians
    return medianOfMedians(nums, low, groupMedian + 1);
}

// Wrapper function to call the median of medians algorithm
int medianOfMediansMethod(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    int result = medianOfMedians(nums, nums.begin(), nums.end());

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return result;
}
