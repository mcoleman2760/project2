#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void medianOfThree(std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto center = std::distance(low, high) / 2 + low;

    // Check that median of three is at the high position
    if (*low == *high || *low == *center || *center == *high) {
        std::iter_swap(low, high);
    }
    else {
        if ((*low < *center && *center < *high) || (*low > *center && *center > *high)) {
            std::iter_swap(center, high);
        }
        if ((*low < *high && *center < *low) || (*low > *high && *center > *low)) {
            std::iter_swap(low, high);
        }
    }
}


std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    medianOfThree(low, high);  // Use median of 3 to pick pivot
    auto pivot = high;
    auto left = low;
    auto right = pivot - 1;

    // hoare Partition loop
    while (true) {
        while (*left < *pivot) {
            ++left;
        }
        while (*right > *pivot) {
            --right;
        }
        if (std::distance(left, right) > 0) {
            std::iter_swap(left, right);
            ++left;
            --right;
        } else {
            break;
        }
    }

    std::iter_swap(left, pivot);
    return left;
}


int quickSelectHelper(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high, std::vector<int>::iterator target) {
    if (high <= low + 9) {
        std::sort(low, high + 1);  // Use simple sort for small arrays
        return *target;
    }

    auto pivot = hoarePartition(nums, low, high);

    // Recursive calls to find the median
    if (pivot > target) {
        return quickSelectHelper(nums, low, pivot - 1, target);
    } else if (pivot == target) {
        return *target;
    }
    return quickSelectHelper(nums, pivot + 1, high, target);
}

int quickSelect(std::vector<int>& nums, int& duration) {
    // starts the clock for duration
    auto start = std::chrono::high_resolution_clock::now();
    int medianIndex = (std::distance(nums.begin(), nums.end()) % 2 == 0) ? (std::distance(nums.begin(), nums.end()) / 2) : ((std::distance(nums.begin(), nums.end()) / 2) + 1);

    auto comp = nums.begin() + medianIndex - 1;
    int median = quickSelectHelper(nums, nums.begin(), nums.end() - 1, comp);
    // ends the clock for duration
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> difference = end - start;
    duration = static_cast<int>(difference.count() * 1000);
    // returns the median 
    return median;
}
