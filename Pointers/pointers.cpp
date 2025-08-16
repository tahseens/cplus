#include "pointers.h"

namespace ptrdemo {

int* makeRawIntBad() {
    // Caller must remember to delete; easy to leak.
    return new int(42);
}

std::unique_ptr<int> makeInt() {
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

void runAllSafe() {
    auto up = makeInt();
    std::cout << "unique_ptr value: " << *up << '\n';

    std::cout << "Safe value: " << safeValue() << '\n';

    vectorWriteGood();

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