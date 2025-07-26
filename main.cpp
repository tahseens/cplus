#include <iostream>
#include <limits>
#include "overandunderflow/Underflow.cpp"
#include "overandunderflow/Overflow.cpp"

int main() {

    Overflow overflowDemo;  // Creates object on stack
    overflowDemo.demonstrate();

    Underflow underflowDemo;
    underflowDemo.demonstrate();

    return 0;
}