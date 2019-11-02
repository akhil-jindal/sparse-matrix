// This is the source file that contains the implementation of
// CSRMatrix and its corresponding functions

#include "csr.hpp"
#include "vec.hpp"

#include <iostream>
#include <cmath>

namespace csr {

// impls

// create a csr matrix
CSRMatrix *create(const int n, const int nnz) {
  CSRMatrix *ptr = nullptr;
  if (n <= 0 || nnz <= 0) {
    std::cout << "Invalid matrix shape" << "\n";
    return ptr;
  }

  ptr = new CSRMatrix;

  if (!ptr) {
    std::cout << "Allocation failed" << "\n";
    return nullptr;
  }

  // initializing indicies, indptr and value arrays
  ptr->indices = nullptr;
  ptr->indptr = nullptr;
  ptr->value = nullptr;
  
  // intializing ptr->n 
  ptr->n = n;

  // getting lengths of arrays
  // indicies and value array have nnz length
  const int indptr_length = n + 1;

  // allocating value array
  ptr->value = new double[nnz];
  // allocating indices array
  ptr->indices = new int[nnz];
  // allocating indptr array
  ptr->indptr = new int[indptr_length];

  return ptr;
}

// destroy a csr matrix
void destroy(CSRMatrix *mat) {
  if (!mat) {
    std::cout << "\tCSR matrix did not exisit\n";
    return;
  }

  if (!mat->value) {
    std::cout << "\tCSR matrix did not have values\n";
    delete mat;
    return;
  }

  std::cout << "\tdeleting CSR matrix and objects: indices, indptrs and value\n";
  delete[] mat->indices;
  delete[] mat->indptr;
  delete[] mat->value;

  delete mat;

}

// assign a row
bool assign_row(CSRMatrix &mat, const int row, const int *cols,
                const double *vals, const int nnz) {
  if (row < 0 || row > mat.n || nnz < 0) return true;
  
  mat.indptr[0] = 0;
  int indptr_index = row + 1;
  mat.indptr[indptr_index] = mat.indptr[row] + nnz;   
  
  // assigning mat.indices and mat.value array
  for (unsigned i=0; i<nnz; ++i) {
    const int start = mat.indptr[row]; // bonus, this is how to get the starting entry of this row

    mat.indices[start + i] = cols[i];
    mat.value[start + i] = vals[i];
    }

  bool fail = false;

  return fail;
}

// extract the diagonal values
bool extract_diag(const CSRMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  bool fail = false;

  // setting n and nnz:
  const int n = A.n;

  // setting diag size to n
  diag.n = A.n;

  //initializing diag array
  for (int i=0; i<n; i++){
    diag.value[i] = 0;
  }

  for (int i=0; i<n; ++i) {
    int start = A.indptr[i];
    int nnz = A.indptr[i+1] - A.indptr[i];
    for (int j=0; j<nnz; ++j) {
      int Aj = A.indices[start+j];
      double Aij = A.value[start+j];
      if (i == Aj) {
        diag.value[i] = Aij;
      }
    }
  }

  return fail;
}

// matrix vector multiplication
bool mv(const CSRMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
  bool fail = false;

  const int n = A.n; // setting matrix.n to n
  
  // setting y size to n
  y.n = n;
  
  //initializing y array
  for (unsigned i=0; i<n; i++){
    y.value[i] = 0;
  }

  // solving for y
  for (int i=0; i<n; ++i){
    int start = A.indptr[i];
    int nnz = A.indptr[i+1] - A.indptr[i];
    // std::cout << "start: " << start << std::endl;
    // std::cout << "nnz: " << nnz << std::endl;
    // std::cout << "Using following to calculate y[i]: " << i << std::endl;
    for (int j=0; j<nnz; ++j) {
      // std::cout << "A[ij]: " << A.value[start+j] << std::endl;
      double Aij = A.value[start+j];
      // std::cout << "A.column[ij]: " << A.indices[start+j] << std::endl;
      int Aj = A.indices[start+j];
      y.value[i] = y.value[i] + Aij * x.value[Aj];
    }
  }
  return fail;
}

}  // namespace csr
