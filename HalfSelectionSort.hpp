#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include <math.h>

int halfSelectionSort(std::vector<int>& nums, int& duration) {
    // Check if the input size is too big for selection sort
    if (nums.size() > 50000) 
    {
        std::cout << "Input size is too big for selection sort (>50,000)." << std::endl;
        return -1;  
    }
    // start the clock to test the duration
    auto start = std::chrono::high_resolution_clock::now();
    // iterators for the for loop
    std::vector<int>::iterator i;
    std::vector<int>::iterator minimum;
    std::vector<int>::iterator it;

    for (i = nums.begin(); i <= nums.begin() + ((nums.size()-1)/2); ++i) {
        // Find the index of the minimum element in the remaining unsorted part
         minimum = i;
         for(it = i + 1; it!= nums.end(); ++it){
            if(*it < *minimum)
            {
                minimum = it;
            } 
         } 
         std::iter_swap(i,minimum);
    }
    //stops the clock and sets the duration
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    // returns the median
    return *(nums.begin() + (nums.size() - 1)/2);
}

