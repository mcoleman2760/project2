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

     if (nums.size() % 2 != 0){ 
      return nums[nums.size()/2];
    }

    else {
      return ((nums[(nums.size()-1)/2] + nums[nums.size()/2])/2);
    }

    return nums[nums.size() / 2];
}

#endif  
