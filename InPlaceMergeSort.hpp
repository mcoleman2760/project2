#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

int inPlaceMergeSort(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> aux(nums.size());

    for (int width = 1; width < nums.size(); width *= 2) {
        for (int i = 0; i < nums.size(); i += 2 * width) {
            int left = i;
            int middle = std::min(i + width, static_cast<int>(nums.size()));
            int right = std::min(i + 2 * width, static_cast<int>(nums.size()));

            std::inplace_merge(nums.begin() + left, nums.begin() + middle, nums.begin() + right);
        }
    }

    //int median = nums[nums.size() / 2];

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();


    if (nums.size() % 2 == 0){
      return nums[((nums.size() / 2) +((nums.size() / 2)-1)) /2 ];
    }
    return nums[nums.size() / 2];
   
}
