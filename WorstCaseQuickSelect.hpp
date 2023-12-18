#pragma once
#include <vector>
#include <algorithm>

std::vector<int> worstCaseQuickSelect() {
    //makes worst case quick select
    int vector_size = 20000;
    std::vector<int> result;
    result.reserve(vector_size);

    for (int i = vector_size; i >= 1; --i) {
        result.push_back(i);
    }

    return result;
}
