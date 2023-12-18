#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "QuickSelect.hpp"

// calculates the median of 5 numbers in 6 comparisons
int medianOfFive(std::vector<int>::iterator low, std::vector<int>::iterator high) {
    std::sort(low, high);
    return *(low + (high - low - 1) / 2);
}

// Recursive function for the median of medians
int medianOfMedians(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int n = high - low;
    if (n <= 5) {
        // If the number of elements is small, sort them and find the median
        std::sort(low, high);
        return *(low + n / 2);
    }

    // Find the median of the different groups of 5 elements using Hoare's partition
    std::vector<int>::iterator groupMedian = low;
    for (std::vector<int>::iterator i = low; i < high; i += 5) {
        std::vector<int>::iterator groupHigh = std::min(i + 5, high);
        int median = medianOfFive(i, groupHigh);
        std::swap(*std::find(i, groupHigh, median), *groupMedian);
        ++groupMedian;
    }

    // Use hoarePartition from quickselect function to partition since this algorithm is a pivot selection method
    std::vector<int>::iterator pivot = hoarePartition(nums, low, groupMedian);

    // uses recursion to find the medians of medians
    return medianOfMedians(nums, low, pivot + 1);
}

// A wrapper function to call the median of medians algorithm
int medianOfMediansMethod(std::vector<int>& nums, int& duration) {
    // start of clock for duration time
    auto start = std::chrono::high_resolution_clock::now();

    int result = medianOfMedians(nums, nums.begin(), nums.end());

    // give the duration time
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // returns the median
    return result;
}
