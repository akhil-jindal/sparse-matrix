// some utility functions used in loading data from ASCII files

#ifndef _AMS562_PROJ1_UTILS_HPP
#define _AMS562_PROJ1_UTILS_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "srcs/coo.hpp"
#include "srcs/csr.hpp"
#include "srcs/vec.hpp"

namespace utils {
// load the vector size
inline int load_vec_size(const std::string &filename) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "cannot open file " << filename << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }
  int n;
  f >> n;
  return n;
}

// load an array to DenseVec
inline void load_vec(const std::string &filename, vec::DenseVec &v) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "cannot open file " << filename << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }
  int n;
  f >> n;
  if (n != v.n) {
    std::cerr << "vector sizes don\'t match, aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }

  // now, assign values
  double buffer;
  for (int i = 0; i < n; ++i) {
    f >> buffer;  // read a double into buffer
    v.value[i] = buffer;
  }

  // close file
  f.close();
}

// get the size and nnz of a sparse matrix that is stored in file
inline void load_mat_sizes(const std::string &filename, int &n, int &nnz) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "cannot open file " << filename << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }

  // extract n and nnz
  f >> n >> nnz;

  // close file
  f.close();
}

// load an sparse matrix with coo to COOMatrix
inline void load_coo(const std::string &filename, coo::COOMatrix &m) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "cannot open file " << filename << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }
  // extract n and nnz
  int n, nnz;
  f >> n >> nnz;
  if (m.n != n || m.nnz != nnz) {
    std::cerr << "COOMatrix sizes don\'t match, aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }

  // create buffer
  int i, j;
  double v;
  for (int k = 0; k < nnz; ++k) {
    f >> i >> j >> v;  // load values from file
    if (coo::assign_ijv(m, i, j, v, k)) {
      std::cerr << "COOMatrix failed to assign (i,j,v)=(" << i << ',' << j
                << ',' << v << "), aborting...\n";
      std::cerr << "error occured at line:" << __LINE__
                << ", in file:" << __FILE__ << "\n";
      std::exit(1);
    }
  }

  // close file
  f.close();
  
}



// load an sparse matrix with coo and convert it to csr
inline void load_csr(const std::string &filename, csr::CSRMatrix &m) {
  std::ifstream f(filename.c_str());
  if (!f.is_open()) {
    std::cerr << "cannot open file " << filename << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }
  // extract n and nnz
  int n, nnz;
  f >> n >> nnz;
  if (m.n != n) {
    std::cerr << "CSRMatrix sizes don\'t match, aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }

  // local construction buffers
  std::vector<int> inds;
  std::vector<double> vs;
  
  int i, j;
  double v;
  int start = 0;
  for (int k = 0; k < nnz; ++k) {
    f >> i >> j >> v;  // load values from file
    if (start == i) {
      inds.push_back(j);
      vs.push_back(v);
      continue;
    }

    // finish a row
    if (csr::assign_row(m, start, inds.data(), vs.data(), inds.size())) {
      std::cerr << "CSRMatrix failed to assign row=" << start
                << ", aborting...\n";
      std::cerr << "error occured at line:" << __LINE__
                << ", in file:" << __FILE__ << "\n";
      std::exit(1);
    }

    // i, j, v store the first entry of next row
    ++start;
    inds.clear();
    vs.clear();
    inds.push_back(j);
    vs.push_back(v);
  }

  // finish the last row
  if (csr::assign_row(m, start, inds.data(), vs.data(), inds.size())) {
    std::cerr << "CSRMatrix failed to assign row=" << start
              << ", aborting...\n";
    std::cerr << "error occured at line:" << __LINE__
              << ", in file:" << __FILE__ << "\n";
    std::exit(1);
  }
  
  // close file
  f.close();
}

}  // namespace utils

#endif
