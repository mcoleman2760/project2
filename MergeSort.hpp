#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

template <typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end) {
    using T = typename std::iterator_traits<Iterator>::value_type;
    std::vector<T> merged(std::distance(begin, end));

    auto left = begin;
    auto right = mid;
    auto mergedIt = merged.begin();

    while (left < mid && right < end) {
        if (*left < *right) {
            *mergedIt++ = *left++;
        } else {
            *mergedIt++ = *right++;
        }
    }

    // Copy the remaining elements from the left and right subarrays
    std::copy(left, mid, mergedIt);
    std::copy(right, end, mergedIt);

    // Copy the merged result back to the original range
    std::copy(merged.begin(), merged.end(), begin);
}

template <typename Iterator>
int mergeSort(Iterator begin, Iterator end, int& duration) {
    auto start = std::chrono::high_resolution_clock::now();

    size_t size = std::distance(begin, end);

    if (size <= 1) {
        auto stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        return *begin;  // Base case: already sorted
    }

    Iterator mid = std::next(begin, size / 2);

    // Recursively sort the left and right halves
    int leftMedian = mergeSort(begin, mid, duration);
    int rightMedian = mergeSort(mid, end, duration);

    // Merge the sorted halves
    merge(begin, mid, end);

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    return (*begin + *(mid - 1)) / 2;  // Return the median of the merged sorted halves
}

int mergeSort(std::vector<int>& nums, int& duration) {
    return mergeSort(nums.begin(), nums.end(), duration);
}

#endif  // MERGE_SORT_HPP
