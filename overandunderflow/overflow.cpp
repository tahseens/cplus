#include <iostream>
#include <climits> // For INT_MAX

class Overflow {
public:
    void demonstrate() {
        std::cout << "Overflow example" << std::endl;
        int max = INT_MAX;
        std::cout << "Initial value: " << max << std::endl;
        max = max + 1; // Causes overflow
        std::cout << "After adding 1: " << max << std::endl;
    }
};