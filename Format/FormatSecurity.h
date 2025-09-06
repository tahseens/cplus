#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

namespace format_security {

class FormatDemo {
public:
    // Demonstrate format string vulnerabilities
    static void demonstrateFormatVulnerabilities();
    
    // Show secure formatting alternatives
    static void demonstrateSecureFormatting();
    
    // Secure file processing example
    static void secureFileProcessing(const std::string& filename);
    
    // Buffer overflow examples
    static void demonstrateBufferIssues();
    
    // Input validation examples
    static void demonstrateInputValidation();
    
    // Run all security demonstrations
    static void runAllDemos();
    
    // Explain pointer dereference
    static void explainPointerDereference();
    
    // Demonstrate stack layout
    static void demonstrateStackLayout();
    
    // Compare with other specifiers
    static void compareWithOtherSpecifiers();
    
    // Show real-world pointer attack
    static void showRealWorldPointerAttack();

private:
    // Helper functions
    static bool isValidFilename(const std::string& filename);
    static std::string sanitizeInput(const std::string& input);
};

} // namespace format_security