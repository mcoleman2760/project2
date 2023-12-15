
#ifndef HALF_SELECTION_SORT_HPP
#define HALF_SELECTION_SORT_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>

int halfSelectionSort(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    size_t size = nums.size();
    size_t halfSize = size / 2;

    // Check if the input size is too big for selection sort
    if (size > 50000) {
        std::cout << "Input size is too big for selection sort (>50,000)." << std::endl;
        duration = -1;  // Indicate that the method was not executed due to input size
        return -1;  // Return an invalid value
    }

    for (size_t i = 0; i < halfSize; ++i) {
        // Find the index of the minimum element in the remaining unsorted part
        auto minIndex = std::min_element(nums.begin() + i, nums.end());

        // Swap the current element with the smallest element found
        std::iter_swap(nums.begin() + i, minIndex);

        // If there are duplicates of the smallest element, swap the first one reached
        auto firstDuplicate = std::find(nums.begin() + i + 1, nums.end(), nums[i]);
        if (firstDuplicate != nums.end()) {
            std::iter_swap(nums.begin() + i + 1, firstDuplicate);
        }
    }

    // Swap the median element into its proper place
    if (size % 2 == 0){
         size_t medianIndex = nums[((size / 2) + ((size / 2)-1)) /2 ];
    }
        size_t medianIndex = size / 2;
    
    
    auto minIndex = std::min_element(nums.begin() + medianIndex, nums.end());
    std::iter_swap(nums.begin() + medianIndex, minIndex);

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    if (nums.size() % 2 == 0){
      return nums[((nums.size() / 2) + ((nums.size() / 2)-1)) /2 ];

    }
    return nums[nums.size() / 2];

    return nums[medianIndex];
 
}

#endif  // HALF_SELECTION_SORT_HPP
