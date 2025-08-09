#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileReader {
public:
    // Old-style file reading
    void readFileOldStyle(const string& filename);
    
    // Modern-style file reading
    void readFileModernStyle(const string& filename);
};