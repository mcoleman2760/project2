#ifndef STANDARD_SORT_HPP
#define STANDARD_SORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

int standardSort(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    std::sort(nums.begin(), nums.end());

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    size_t size = nums.size();
    size_t middleIndex = size / 2;

    // Calculate the median
    int median;
    if (size % 2 == 0) {
        // Even-sized vector
        median = (nums[middleIndex - 1] + nums[middleIndex]) / 2;
    } else {
        // Odd-sized vector
        median = nums[middleIndex];
    }

    return median;
}

#endif  // STANDARD_SORT_HPP
