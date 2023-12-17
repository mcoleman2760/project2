
#include <vector>
#include <algorithm>
#include <chrono>

void percDown(std::vector<int>& heap, std::vector<int>::size_type hole){
    //uses the percDown function found in the textbook
    int child;
    int tmp = std::move(heap[0]); 
    

    // While node has at least one child
    for (int tmp = std::move(heap[0]); hole * 2 < heap.size(); hole = child) {
        // Finds  smaller child 
        child = 2*hole;
        if(child + 1 < heap.size() && heap[child] > heap[child+1]) 
        {
            ++child;
        }
        
        // swaps if child has a lower value then node
        if(tmp > heap[child])
         {
            heap[hole] = std::move(heap[child]); 
            hole = child;
        }
        else 
        { 
            break;
        }
    }
    
   // Puts temp value in hole
    heap[hole] = std::move(tmp);
}

void buildHeap(std::vector<int>& heap){
    //uses the bui
     for (int i = (heap.size() - 1) / 2; i > 0; i--) {
        heap[0] = heap[i];
        percDown(heap, i);
    }
}

int halfHeapSort(std::vector<int>& nums, int& duration){
     //starts clock for duration
     auto start = std::chrono::high_resolution_clock::now();

    nums.push_back(std::move(nums[0]));

    // used buildHeap function for the vector
    buildHeap(nums);

    int s = nums.size() - 2;
    for (int i = 0; i < s / 2; i++) {
       
        nums[0] = nums[nums.size()-1];
        nums.pop_back();

        percDown(nums,1);
    }
    //stops the clock for duration
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    //finds the median and returns it
    int median = nums[1];
    return median;

        
}

