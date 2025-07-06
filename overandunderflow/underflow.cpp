#include <iostream>
#include <limits>

int main() {
    int minInt = std::numeric_limits<int>::min();
    std::cout << "Minimum int value: " << minInt << std::endl;

    // Underflow happens here:
    int underflow = minInt - 1;

    std::cout << "After underflow (minInt - 1): " << underflow << std::endl;

    return 0;
}
