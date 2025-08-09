#include <iostream>
#include <limits>
#include "overandunderflow/Underflow.cpp"
#include "overandunderflow/Overflow.cpp"
#include "files/FileReader.h"

int main() {

    Overflow overflowDemo;  // Creates object on stack
    overflowDemo.demonstrate();

    Underflow underflowDemo;
    underflowDemo.demonstrate();


    FileReader reader;
    std::string filename = "example.txt";

    std::cout << "Reading using old style:\n";
    reader.readFileOldStyle(filename);

    std::cout << "\nReading using modern style:\n";
    reader.readFileModernStyle(filename);


    return 0;
}