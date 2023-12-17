#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>  // for std::merge

int mergeSort(std::vector<int>& nums, int& duration) {
    //starts the clock for duration
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> aux(nums.size());
    // 
    for (int width = 1; width < nums.size(); width *= 2) {
        for (int i = 0; i < nums.size(); i += 2 * width) {
            int left = i;
            int middle = std::min(i + width, static_cast<int>(nums.size()));
            int right = std::min(i + 2 * width, static_cast<int>(nums.size()));
            //use the function std::merge to merge the different parts of the vector
            std::merge(nums.begin() + left, nums.begin() + middle,
                       nums.begin() + middle, nums.begin() + right,
                       aux.begin() + left);
        }

        std::copy(aux.begin(), aux.end(), nums.begin());
    }
   //ends clock for the duration 
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    //returns the median for odd and even numbered vectors
    if (nums.size() % 2 == 0){
      return nums[((nums.size() / 2) +((nums.size() / 2)-1)) /2 ];

    }
    return nums[nums.size() / 2];

}
