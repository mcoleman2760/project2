#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>  // for std::merge

int mergeSort(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    int median = 0;

    if (nums.size() > 1) {
        auto middle = nums.begin() + nums.size() / 2;

        int medianLeft = mergeSort(std::vector<int>(nums.begin(), middle), duration);
        int medianRight = mergeSort(std::vector<int>(middle, nums.end()), duration);

        std::vector<int> merged;
        std::merge(nums.begin(), middle, middle, nums.end(), std::back_inserter(merged));
        std::copy(merged.begin(), merged.end(), nums.begin());

        median = (medianLeft + medianRight) / 2;
    } else if (!nums.empty()) {
        median = nums[0];
    }

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    return median;
}
