#include "FileReader.h"  // Include the header file for FileReader

using namespace std;

    // Old-style file reading
    void FileReader::readFileOldStyle(const string& filename) {
        ifstream file(filename.c_str()); // C-style string for compatibility
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
    void FileReader::readFileModernStyle(const string& filename) {
        ifstream file(filename); // RAII handles closing
        if (!file) {
            cerr << "Failed to open file (modern style).\n";
            return;
        }

        for (string line; getline(file, line); ) {
            cout << line << '\n';
        }
    }

