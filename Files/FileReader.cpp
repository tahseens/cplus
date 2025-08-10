#include "FileReader.h"

using namespace std;

FileReader::FileReader(const string& filename) : filename(filename) {

}

// Old-style file reading
void FileReader::readFileOldStyle() {
    ifstream file(filename); // Modern C++ - no c_str() needed
    if (!file.is_open()) {
        cerr << "Failed to open file (old style).\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }

    file.close(); // Explicit close
}

// Modern-style file reading
void FileReader::readFileModernStyle() {
    ifstream file(filename); // Modern C++ - no c_str() needed
    if (!file) {
        cerr << "Failed to open file (modern style).\n";
        return;
    }

    for (string line; getline(file, line); ) {
        cout << line << '\n';
    }
}

