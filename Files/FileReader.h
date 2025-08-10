#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileReader {

private:
    string filename;
public:

    FileReader(const string& filename);
    // Old-style file reading
    void readFileOldStyle();
    // Modern-style file reading
    void readFileModernStyle();
};