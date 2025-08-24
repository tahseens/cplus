#include "pointers.h"

namespace ptrdemo {

int* makeRawIntBad() {
    // Caller must remember to delete; easy to leak.
    return new int(42);
}

std::unique_ptr<int> makeSafeInt() {
    return std::make_unique<int>(42);
}

int* danglingPointer() {
    int x = 10;
    return &x; // BAD: address becomes invalid after return.
}

int safeValue() {
    int x = 10;
    return x; // Copy (likely NRVO) – safe.
}

void rawArrayWriteBad() {
    int* arr = new int[3];
    for (int i = 0; i < 5; ++i) { // Writes past end (i=3,4) -> UB.
        arr[i] = i;
    }
    delete[] arr;
}

void vectorWriteGood() {
    std::vector<int> v(3);
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = static_cast<int>(i);
    }
    for (int n : v) std::cout << n << ' ';
    std::cout << '\n';
}

void doubleDeleteBad() {
    int* p = new int(7);
    delete p;
    // delete p; // If uncommented: double free (UB).
}

std::shared_ptr<std::string> makeSharedString(const std::string& s) {
    return std::make_shared<std::string>(s);
}

void observe(const int* p) {
    if (p) std::cout << "Observed: " << *p << '\n';
}

void uncheckedDereferenceBad(int* p) {
    // No null check – crash risk if p is null.
    *p = 5;
}

void checkedDereferenceGood(int* p) {
    if (!p) {
        std::cerr << "Null pointer\n";
        return;
    }
    *p = 5;
}

void oldStyleArrayBad() {
    std::cout << "\n=== OLD STYLE ARRAY (BAD) ===\n";
    
    // Problem 1: Fixed size
    int arr[3];  // Can't grow
    
    // Problem 2: No bounds checking
    for (int i = 0; i < 5; ++i) {  // Oops, accessing arr[3] and arr[4]!
        arr[i] = i * 10;  // Undefined behavior
    }
    
    // Problem 3: Manual memory for dynamic size
    int* dynArr = new int[5];
    for (int i = 0; i < 5; ++i) {
        dynArr[i] = i * 20;
    }
    
    // Problem 4: Easy to forget cleanup
    // delete[] dynArr;  // Oops, forgot this = memory leak!
    
    // Problem 5: No size information
    // How big is dynArr? We have to remember!
    
    std::cout << "Old style completed (with bugs)\n";
}

void modernVectorGood() {
    std::cout << "\n=== MODERN VECTOR (GOOD) ===\n";
    
    // Advantage 1: Dynamic size
    std::vector<int> v;
    
    // Advantage 2: Safe growing
    for (int i = 0; i < 10; ++i) {
        v.push_back(i * 10);  // Grows automatically
    }
    
    // Advantage 3: Size information
    std::cout << "Vector size: " << v.size() << '\n';
    
    // Advantage 4: Safe access option
    try {
        std::cout << "Safe access v.at(5): " << v.at(5) << '\n';
        // v.at(50);  // Would throw exception instead of crash
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
    
    // Advantage 5: Automatic cleanup (RAII)
    // No delete needed - destructor handles it
    
    // Advantage 6: Works with STL algorithms
    std::sort(v.begin(), v.end());
    
    std::cout << "Sorted vector: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

void vectorRangeExample() {
    std::cout << "\n=== VECTOR RANGE OPERATIONS ===\n";
    
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {10, 20, 30};
    
    std::cout << "Before merge: ";
    for (int x : v1) std::cout << x << ' ';
    std::cout << '\n';
    
    // Add entire range - impossible with old arrays!
    v1.insert(v1.end(), v2.begin(), v2.end());
    
    std::cout << "After merge: ";
    for (int x : v1) std::cout << x << ' ';
    std::cout << '\n';
    
    // Reserve capacity for performance
    std::vector<int> v3;
    v3.reserve(1000);  // Avoid reallocations
    for (int i = 0; i < 1000; ++i) {
        v3.push_back(i);
    }
    std::cout << "Added 1000 elements efficiently\n";
}

void runAllSafe() {
    auto up = makeSafeInt();
    std::cout << "unique_ptr value: " << *up << '\n';

    std::cout << "Safe value: " << safeValue() << '\n';

    vectorWriteGood();
    
    // Add the new examples
    oldStyleArrayBad();
    modernVectorGood();
    vectorRangeExample();

    auto sp1 = makeSharedString("hello");
    auto sp2 = sp1;
    std::cout << "shared_ptr use_count: " << sp1.use_count() << '\n';

    int local = 9;
    observe(&local);

    int z = 0;
    checkedDereferenceGood(&z);
    std::cout << "Checked assign: " << z << '\n';
}

} // namespace ptrdemo