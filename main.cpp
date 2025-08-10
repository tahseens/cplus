#include <iostream>
#include <limits>
#include "overandunderflow/Underflow.cpp"
#include "overandunderflow/Overflow.cpp"
#include "Files/FileReader.h"

using namespace std;

int main() {

    Overflow overflowDemo;  // Creates object on stack
    overflowDemo.demonstrate();

    Underflow underflowDemo;
    underflowDemo.demonstrate();


    string filename = "example.txt";
    FileReader reader(filename);


    cout << "Reading using old style:\n";
    reader.readFileOldStyle();

    cout << "\nReading using modern style:\n";
    reader.readFileModernStyle();


    return 0;
}