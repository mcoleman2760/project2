#ifndef STANDARD_SORT_HPP
#define STANDARD_SORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

int standardSort(std::vector<int>& nums, int& duration) {
  // starts the clock to find the duration
    auto start = std::chrono::high_resolution_clock::now();
    // use std::sort function to sort the vector
    std::sort(nums.begin(), nums.end());
    //end of clock for duration
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // finds the median for even and odd numbered vectors
    if (nums.size() % 2 == 0){
      return nums[((nums.size() / 2) +((nums.size() / 2)-1)) /2 ];

    }
    return nums[nums.size() / 2];

}

#endif 
