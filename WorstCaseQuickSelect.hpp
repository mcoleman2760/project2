#include <vector>
#include <algorithm>

std::vector<int> worstCaseQuickSelect() {
    std::vector<int> input(20000);

    // Fill the vector with numbers from 1 to 20000
    for (int i = 0; i < 20000; ++i) {
        input[i] = i + 1;
    }

    // Shuffle the vector to avoid any patterns
    std::random_shuffle(input.begin(), input.end());

    return input;
}
