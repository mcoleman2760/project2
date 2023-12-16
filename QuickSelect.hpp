#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int pivot = *low;
    auto i = low - 1;
    auto j = high + 1;

    while (true) {
        do {
            i++;
        } while (*i < pivot);

        do {
            j--;
        } while (*j > pivot);

        if (i >= j) {
            return j;
        }

        std::iter_swap(i, j);
    }
}

// Function to perform quick select
int quickSelect(std::vector<int>& nums, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    // Using Hoare's partition
    std::vector<int>::iterator low = nums.begin();
    std::vector<int>::iterator high = nums.end() - 1;
    int k = nums.size() / 2; // Change k to the desired position (e.g., median)

    while (low <= high) {
        std::vector<int>::iterator pivot = hoarePartition(nums, low, high);

        if (pivot == nums.begin() + k) {
            break; // Found the element at the k-th position
        } else if (pivot < nums.begin() + k) {
            low = pivot + 1;
        } else {
            high = pivot - 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return *(nums.begin() + k);
}
