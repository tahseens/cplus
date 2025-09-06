#include "FormatSecurity.h"
#include <fstream>
#include <algorithm>

using namespace std;

namespace format_security {

void FormatDemo::demonstrateFormatVulnerabilities() {
    cout << "\n=== FORMAT SECURITY VULNERABILITIES ===\n";
    
    string userInput = "test%x%x%x%x%n";  // Simulated malicious input
    
    // ❌ VULNERABLE: User input as format string
    cout << "❌ VULNERABLE PATTERNS (DO NOT USE):\n";
    cout << "printf(userInput.c_str())     // Format string attack\n";
    cout << "sprintf(buf, userInput)       // Buffer + format attack\n";
    cout << "fprintf(log, userMessage)     // Log injection\n";
    
    cout << "\nMalicious input example: \"" << userInput << "\"\n";
    cout << "This could read memory, crash program, or execute code!\n";
    
    // Show what the vulnerable code would look like (commented)
    cout << "\n// ❌ DON'T DO THIS:\n";
    cout << "// printf(\"" << userInput << "\");  // Dangerous!\n";
}

void FormatDemo::demonstrateSecureFormatting() {
    cout << "\n=== SECURE FORMATTING SOLUTIONS ===\n";
    
    string userInput = "user%x%x%data";
    string filename = "data.txt";
    int lineCount = 42;
    double fileSize = 1024.5;
    
    cout << "✅ SECURE METHODS:\n\n";
    
    // 1. Fixed format strings with printf family
    cout << "1. Fixed format with printf:\n";
    printf("   File: %s, Lines: %d, Size: %.1f KB\n", 
           filename.c_str(), lineCount, fileSize);
    printf("   User input (safe): %s\n", userInput.c_str());
    
    // 2. C++ streams (always safe)
    cout << "\n2. C++ streams (always safe):\n";
    cout << "   File: " << filename << ", Lines: " << lineCount 
         << ", Size: " << fileSize << " KB\n";
    cout << "   User input: " << userInput << '\n';
    
    // 3. stringstream for complex formatting
    cout << "\n3. stringstream for complex formatting:\n";
    stringstream ss;
    ss << "   Processing " << filename << " (" << lineCount 
       << " lines, " << fileSize << " KB)";
    cout << ss.str() << '\n';
    
    // 4. snprintf with bounds checking
    cout << "\n4. snprintf with bounds checking:\n";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
             "   Secure: %.50s has %d lines", filename.c_str(), lineCount);
    cout << buffer << '\n';
    
    // 5. Modern C++20 format (if available)
    cout << "\n5. C++20 std::format (type-safe):\n";
    #if __cplusplus >= 202002L
    string formatted = std::format("   Modern: {} has {} lines", filename, lineCount);
    cout << formatted << '\n';
    #else
    cout << "   (std::format requires C++20)\n";
    #endif
}

void FormatDemo::demonstrateBufferIssues() {
    cout << "\n=== BUFFER OVERFLOW PREVENTION ===\n";
    
    string longFilename = "very_long_filename_that_could_overflow_buffer.txt";
    
    cout << "❌ VULNERABLE: Unbounded sprintf\n";
    cout << "char buf[20]; sprintf(buf, \"File: %s\", longName); // Overflow!\n";
    
    cout << "\n✅ SECURE ALTERNATIVES:\n";
    
    // 1. snprintf with size limit
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "File: %.30s", longFilename.c_str());
    cout << "1. snprintf: " << buffer << '\n';
    
    // 2. String concatenation (no buffer limits)
    string safeResult = "File: " + longFilename;
    cout << "2. string concat: " << safeResult.substr(0, 50) << "...\n";
    
    // 3. stringstream (dynamic sizing)
    stringstream ss;
    ss << "File: " << longFilename;
    cout << "3. stringstream: " << ss.str().substr(0, 50) << "...\n";
}

void FormatDemo::demonstrateInputValidation() {
    cout << "\n=== INPUT VALIDATION ===\n";
    
    vector<string> testInputs = {
        "normal_file.txt",
        "../../../etc/passwd",  // Path traversal
        "file%x%x%n.txt",       // Format specifiers
        "",                     // Empty
        "file\nwith\nnewlines.txt", // Control characters
        string(1000, 'A') + ".txt"  // Very long
    };
    
    for (const auto& input : testInputs) {
        cout << "\nTesting: \"" << input.substr(0, 30);
        if (input.length() > 30) cout << "...";
        cout << "\"\n";
        
        if (isValidFilename(input)) {
            string sanitized = sanitizeInput(input);
            cout << "✅ Valid (sanitized): \"" << sanitized << "\"\n";
        } else {
            cout << "❌ Invalid/Rejected\n";
        }
    }
}

void FormatDemo::secureFileProcessing(const string& filename) {
    cout << "\n=== SECURE FILE PROCESSING ===\n";
    
    // Validate input
    if (!isValidFilename(filename)) {
        cout << "❌ Invalid filename rejected\n";
        return;
    }
    
    string safeFilename = sanitizeInput(filename);
    cout << "Processing file: " << safeFilename << '\n';
    
    ifstream file(safeFilename);
    if (!file) {
        // ✅ SECURE: Safe error reporting
        cout << "❌ Failed to open file: " << safeFilename << '\n';
        return;
    }
    
    string line;
    int lineNum = 1;
    cout << "✅ File contents:\n";
    
    while (getline(file, line) && lineNum <= 10) {  // Limit output
        // ✅ SECURE: Safe line output (no format vulnerabilities)
        cout << "Line " << lineNum << ": " << line << '\n';
        lineNum++;
    }
    
    printf("✅ Processed %d lines from: %s\n", lineNum - 1, safeFilename.c_str());
}

bool FormatDemo::isValidFilename(const string& filename) {
    // Check for empty
    if (filename.empty()) return false;
    
    // Check for path traversal
    if (filename.find("..") != string::npos) return false;
    
    // Check for control characters
    for (char c : filename) {
        if (c < 32 && c != '\t') return false;  // No control chars except tab
    }
    
    // Check length
    if (filename.length() > 255) return false;
    
    // Check for format specifiers (basic check)
    if (filename.find('%') != string::npos) return false;
    
    return true;
}

string FormatDemo::sanitizeInput(const string& input) {
    string result = input;
    
    // Remove/replace dangerous characters
    replace(result.begin(), result.end(), '%', '_');
    replace(result.begin(), result.end(), '\n', '_');
    replace(result.begin(), result.end(), '\r', '_');
    
    // Truncate if too long
    if (result.length() > 100) {
        result = result.substr(0, 100);
    }
    
    return result;
}

void FormatDemo::runAllDemos() {
    cout << "=== FORMAT SECURITY DEMONSTRATION ===\n";
    
    demonstrateFormatVulnerabilities();
    explainPointerDereference();        // Add this
    demonstrateStackLayout();           // Add this
    demonstrateSecureFormatting();
    compareWithOtherSpecifiers();       // Add this
    showRealWorldPointerAttack();       // Add this
    demonstrateBufferIssues();
    demonstrateInputValidation();
    secureFileProcessing("example.txt");
    
    cout << "\n=== END DEMONSTRATION ===\n";
}

void FormatDemo::explainPointerDereference() {
    cout << "\n=== WHY %s CAUSES POINTER DEREFERENCE ===\n";
    
    cout << "🔍 HOW %s WORKS:\n";
    cout << "%s = 'Print string starting at this memory address'\n\n";
    
    cout << "✅ NORMAL %s usage:\n";
    const char* validString = "Hello World";
    printf("Valid: %%s with real pointer -> %s\n", validString);
    cout << "printf reads FROM address " << (void*)validString << '\n';
    
    cout << "\n💀 MALICIOUS %s usage:\n";
    cout << "printf(\"%s%s%s%s\");  // No arguments provided!\n\n";
    
    cout << "What printf does:\n";
    cout << "1. Reads stack value #1 (e.g., 0x401000) -> treats as pointer\n";
    cout << "2. Tries to read string starting at 0x401000\n";
    cout << "3. Reads stack value #2 (e.g., 0x7fff1234) -> treats as pointer\n";
    cout << "4. Tries to read string starting at 0x7fff1234\n";
    cout << "5. Continues for each %s...\n\n";
    
    cout << "💥 WHAT GOES WRONG:\n";
    cout << "- Stack values are usually NOT valid string pointers\n";
    cout << "- Reading from random addresses causes SEGFAULT\n";
    cout << "- If address happens to be valid, leaks memory contents\n";
    cout << "- Could read sensitive data like passwords, keys\n";
}

void FormatDemo::demonstrateStackLayout() {
    cout << "\n=== STACK LAYOUT DURING PRINTF ATTACK ===\n";
    
    // Simulate what's on the stack
    cout << "📚 TYPICAL STACK LAYOUT:\n";
    cout << "Stack Address  | Value      | What %s would do\n";
    cout << "---------------|------------|------------------\n";
    cout << "0x7fff1000     | 0x401234   | Read string at 0x401234 (crash/leak)\n";
    cout << "0x7fff1008     | 0x00000042 | Read string at 0x42 (crash)\n";
    cout << "0x7fff1010     | 0x7fff2000 | Read string at 0x7fff2000 (leak)\n";
    cout << "0x7fff1018     | 0xDEADBEEF | Read string at 0xDEADBEEF (crash)\n";
    
    cout << "\n🎯 ATTACK SCENARIO:\n";
    cout << "Attacker inputs: \"Show data: %s %s %s %s\"\n";
    cout << "printf tries to:\n";
    cout << "1. Print string at 0x401234 -> might leak code/data\n";
    cout << "2. Print string at 0x42 -> crashes (invalid address)\n";
    cout << "3. Print string at 0x7fff2000 -> leaks stack data\n";
    cout << "4. Print string at 0xDEADBEEF -> crashes\n";
    
    cout << "\n🛡️ WHY COUT IS SAFE:\n";
    cout << "cout << \"Show data: %s %s %s %s\";  // Just prints literal text\n";
    cout << "No pointer dereferencing - % has no special meaning!\n";
}

void FormatDemo::compareWithOtherSpecifiers() {
    cout << "\n=== COMPARISON WITH OTHER FORMAT SPECIFIERS ===\n";
    
    cout << "📊 WHAT DIFFERENT SPECIFIERS DO:\n\n";
    
    cout << "%d = Read stack value as INTEGER\n";
    cout << "     Danger level: Low (just shows numbers)\n";
    cout << "     Example: 0x401234 displayed as 4198964\n\n";
    
    cout << "%x = Read stack value as HEX\n";
    cout << "     Danger level: Medium (reveals addresses/data)\n";
    cout << "     Example: 0x401234 displayed as 401234\n\n";
    
    cout << "%s = Read stack value as POINTER TO STRING\n";
    cout << "     Danger level: HIGH (dereferences memory)\n";
    cout << "     Example: 0x401234 -> reads memory starting at 0x401234\n\n";
    
    cout << "%n = WRITE to memory address\n";
    cout << "     Danger level: CRITICAL (memory corruption)\n";
    cout << "     Example: writes byte count to address in stack value\n\n";
    
    cout << "🔥 WHY %s IS ESPECIALLY DANGEROUS:\n";
    cout << "- Actually READS from arbitrary memory locations\n";
    cout << "- Can traverse memory structures\n";
    cout << "- Often causes immediate crashes (easier to detect in testing)\n";
    cout << "- Can leak large amounts of data in one go\n";
}

void FormatDemo::showRealWorldPointerAttack() {
    cout << "\n=== REAL WORLD POINTER DEREFERENCE ATTACK ===\n";
    
    cout << "🎯 HISTORICAL EXAMPLE (wu-ftpd vulnerability):\n";
    cout << "Vulnerable code:\n";
    cout << "syslog(LOG_INFO, user_input);  // user_input from FTP command\n\n";
    
    cout << "Attacker sends FTP command:\n";
    cout << "USER %s%s%s%s%s%s%s%s\n\n";
    
    cout << "What happens:\n";
    cout << "1. syslog calls printf-like function with user input as format\n";
    cout << "2. Each %s tries to print a string from stack addresses\n";
    cout << "3. Reveals memory contents (passwords, config, etc.)\n";
    cout << "4. Attacker gets sensitive information from server\n\n";
    
    cout << "✅ SECURE VERSION:\n";
    cout << "syslog(LOG_INFO, \"User login attempt: %s\", user_input);\n";
    cout << "Now user_input is data, not format instructions!\n";
}
}