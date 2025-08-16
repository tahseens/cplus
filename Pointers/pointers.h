#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace ptrdemo {

// BAD: raw owning pointer (leak risk if not deleted)
int* makeRawIntBad();

// GOOD: unique_ptr owning integer
std::unique_ptr<int> makeInt();

// BAD: returns pointer to local variable (dangling)
int* danglingPointer();

// GOOD: returns value safely
int safeValue();

// BAD: manual array + potential overflow
void rawArrayWriteBad();

// GOOD: std::vector replacement
void vectorWriteGood();

// BAD: double delete example (do not run in production)
void doubleDeleteBad();

// GOOD: shared ownership demo
std::shared_ptr<std::string> makeSharedString(const std::string& s);

// GOOD: non-owning raw pointer (observer) usage pattern
void observe(const int* p);

// BAD: unchecked pointer dereference
void uncheckedDereferenceBad(int* p);

// GOOD: checked dereference
void checkedDereferenceGood(int* p);

// Run all demos (safe ones only)
void runAllSafe();

} // namespace ptrdemo