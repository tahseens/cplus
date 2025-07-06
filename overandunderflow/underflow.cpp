#include <iostream>
#include <limits>

int main() {

    int minInt = std::numeric_limits<int>::min();
    std::cout << "Minimum int value: " << minInt << std::endl;

   if (minInt == std::numeric_limits<int>::min()) {
        std::cout<<"inside if condition"<<std::endl;
        std::cout << "Underflow risk if subtracting 1!" << std::endl;
        return 0;
    }

    // Underflow happens here:
    int underflow = minInt - 1;

    std::cout << "After underflow (minInt - 1): " << underflow << std::endl;

    return 0;
}
