#ifndef HALFHEAPSORT_HPP
#define HALFHEAPSORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

void percDown(std::vector<int>& heap, std::vector<int>::size_type hole){
    int tmp = std::move(heap[hole]);

    while (hole > 0 && tmp > heap[(hole - 1) / 2]) {
        heap[hole] = std::move(heap[(hole - 1) / 2]);
        hole = (hole - 1) / 2;
    }

    heap[hole] = std::move(tmp);
}

void buildHeap(std::vector<int>& heap){
     for (std::vector<int>::size_type i = heap.size() / 2; i > 0; --i) {
        percDown(heap, i);
    }
}

int halfHeapSort(std::vector<int>& nums, int& duration){
     auto start = std::chrono::high_resolution_clock::now();

    // Build max heap
    buildHeap(nums);

    // Perform heap sort
    for (std::vector<int>::size_type i = nums.size() / 2; i < nums.size(); ++i) {
        std::swap(nums[0], nums[i]);
        percDown(nums, i);
    }

    int median = nums[nums.size() / 2];

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    return median;
}




#endif // HALFHEAPSORT_HPP
