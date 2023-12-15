#ifndef HALFHEAPSORT_HPP
#define HALFHEAPSORT_HPP

#include <vector>
#include <algorithm>
#include <chrono>

void percDown(std::vector<int>& heap, std::vector<int>::size_type hole){
    int tmp = std::move(heap[hole]);

    while (2 * hole + 1 < heap.size() - 1) {
        std::vector<int>::size_type leftChild = 2 * hole + 1;
        std::vector<int>::size_type rightChild = leftChild + 1;

        // If the right child exists and is greater than or equal to the left child
        if (rightChild < heap.size() - 1 && heap[rightChild] >= heap[leftChild]) {
            ++leftChild; // Move to the left child
        }

        // If the value in the hole is greater than or equal to the larger of the children, break
        if (tmp >= heap[leftChild]) {
            break;
        }

        heap[hole] = std::move(heap[leftChild]);
        hole = leftChild;
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
    for (std::vector<int>::size_type i = nums.size() / 2; i > 0; i--) {
        std::swap(nums[0], nums[i]);
        percDown(nums, nums.size());
    }

  //  int median = nums[nums.size() / 2];

    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    if (nums.size() % 2 == 0){
      return nums[((nums.size() / 2) +((nums.size() / 2)-1)) /2 ];

    }
    return nums[nums.size() / 2];

    
}




#endif // HALFHEAPSORT_HPP
