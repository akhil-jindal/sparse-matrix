// source code of COO format

#include <iostream>
#include <cmath>
#include "coo.hpp"
#include "vec.hpp"

namespace coo {

// create a csr matrix
COOMatrix *create(const int n, const int nnz) {
  COOMatrix *ptr = nullptr;
  if (n <= 0 || nnz <= 0) {
    std::cout << "Invalid matrix shape" << "\n";
    return ptr;
  }

  ptr = new COOMatrix;

  if (!ptr) {
    std::cout << "Allocation failed" << "\n";
    return nullptr;
  }

  // initializing indicies, indptr and value arrays
  ptr->i = nullptr;
  ptr->j = nullptr;
  ptr->v = nullptr;

  // intializing ptr->n 
  ptr->n = n;
  // intializing ptr->nnz
  ptr->nnz = nnz;
  
  // allocating arrays
  ptr->i = new int[nnz];
  ptr->j = new int[nnz];
  ptr->v = new double[nnz];

  return ptr;
}

// destroy a csr matrix
void destroy(COOMatrix *mat) {
  if (!mat) {
    std::cout << "\tCOO matrix did not exisit\n";
    return;
  }

  if (!mat->v) {
    std::cout << "\tCOO matrix did not have values\n";
    delete mat;
    return;
  }
  
  std::cout << "\tdeleting COO matrix objects: indices, indptrs and value\n";
  delete[] mat->i;
  delete[] mat->j;
  delete[] mat->v;

  delete mat;
}

// assign a triplet (i,j,v)
bool assign_ijv(COOMatrix &mat, const int i, const int j, const double v,
                const int nnz_index) {
  bool fail = false;

  mat.i[nnz_index] = i;
  mat.j[nnz_index] = j;
  mat.v[nnz_index] = v;

  return fail;
}

// extract the diagonal values
bool extract_diag(const COOMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  bool fail = false;

  // setting n and nnz:
  const int n = A.n;
  const int nnz = A.nnz; // setting matrix.nnz to nnz

  // setting diag size to n
  diag.n = A.n;

 
  //initializing y array
  for (int i=0; i<n; i++){
    diag.value[i] = 0;
  }

  for (int i=0; i<nnz; ++i){
    int row_i = A.i[i];
    int col_i = A.j[i];

    if (col_i == row_i) {
      diag.value[row_i] = A.v[i];
    }
  }

  return fail;
}

// matrix vector multiplication
bool mv(const COOMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
  bool fail = false;
  const int n = A.n; // setting matrix.n to n
  const int nnz = A.nnz; // setting matrix.nnz to nnz
  
  // setting y size to n
  y.n = n;
  
  //initializing y array
  for (int i=0; i<n; i++){
    y.value[i] = 0;
  }
  
  // std::cout << "n: " << n << std::endl;
  for (int i=0; i<nnz; ++i){

    int row_i = A.i[i];
    int col_i = A.j[i];

    y.value[row_i] = y.value[row_i] + A.v[i]*x.value[col_i];
  }
    return fail;
}

} // namespace coo
