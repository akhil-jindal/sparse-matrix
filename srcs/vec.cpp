// This is the source file that contains the implementation of
// DenseVec and its corresponding functions

// You should not touch this file!

#include "vec.hpp"

namespace vec {

// create a vector
DenseVec *create(const int n) {
  DenseVec *ptr = nullptr;
  if (n <= 0) {
    // invalid size, return nullptr
    return ptr;
  }
  // first allocate a pointer that points to DenseVec
  ptr = new DenseVec;

  // allocation failed
  if (!ptr) {
    return nullptr;
  }

  ptr->value = nullptr;
  ptr->n = n;

  // allocate the value array
  ptr->value = new double[n];
  if (!ptr->value) {
    // value is failed to be initialized, but ptr is already allocated.
    // So a cleanup is needed.
    delete ptr;
    return nullptr;
  }

  return ptr;
}

// destroy a vector
void destroy(DenseVec *vec) {
  if (!vec) {
    // if the pointer is null, direct return, do nothing
    return;
  }

  if (!vec->value) {
    delete vec;
    return;
  }

  delete[] vec->value;
  delete vec;
}

}  // namespace vec
