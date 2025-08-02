#include <iostream>
#include <fstream>
#include <string>

class FileReader {
public:
    // Old-style file reading
    void readFileOldStyle(const std::string& filename) {
        std::ifstream file(filename.c_str()); // C-style string for compatibility
        if (!file.is_open()) {
            std::cerr << "Failed to open file (old style).\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }

        file.close(); // Explicit close
    }

    // Modern-style file reading
    void readFileModernStyle(const std::string& filename) {
        std::ifstream file(filename); // RAII handles closing
        if (!file) {
            std::cerr << "Failed to open file (modern style).\n";
            return;
        }

        for (std::string line; std::getline(file, line); ) {
            std::cout << line << '\n';
        }
    }
};
