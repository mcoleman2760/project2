#ifndef HALFHEAPSORT_HPP
#define HALFHEAPSORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

void percDown(std::vector<int>& heap, std::vector<int>::size_type hole){
    int value = heap[0]; // value to be inserted into the hole

    while (hole * 2 + 1 < heap.size()) {
        std::vector<int>::size_type child = hole * 2 + 1;

        if (child + 1 < heap.size() && heap[child + 1] == heap[child]) {
            // If the right child exists and is equal to the left child, use it instead
            ++child;
        }

        if (heap[child] > value) {
            heap[hole] = heap[child];
            hole = child;
        } else {
            break;
        }
    }

    heap[hole] = value;
}

void buildHeap(std::vector<int>& heap){
     for (std::vector<int>::size_type i = heap.size() / 2; i > 0; i--) {
        percDown(heap, i);
    }
}

int halfHeapSort(std::vector<int>& nums, int& duration){
     auto start = std::chrono::high_resolution_clock::now();
  // Move the first element to the back
    std::swap(nums[0], nums[nums.size() - 1]);

    // Build max heap on the first half of the vector
    buildHeap(nums);

    // Perform half heap sort on the second half of the vector
    for (std::vector<int>::size_type i = nums.size() - 1; i > nums.size() / 2; --i) {
        // Swap root (maximum element) with the last element in the unsorted portion
        std::swap(nums[0], nums[i]);

        // Restore heap property on the reduced heap and store the median value
        int median = nums.size() / 2;

        if (i == nums.size() / 2 + 1) {
            return median;
        }
    }

    // In case the vector size is even, return the median of the two middle elements
    return (nums[nums.size() / 2] + nums[nums.size() / 2 - 1]) / 2;
}




#endif // HALFHEAPSORT_HPP
