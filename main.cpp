//  The main test program

#include <cmath>

#include "utils.hpp"  // matrix and vector interfaces are included here

#define FAIL "\033[0;31mFAIL\033[0m"
#define PASS "\033[0;32mPASS\033[0m"

double nrm2_error(const vec::DenseVec &x, const vec::DenseVec &x_ref) {
  double e = 0.0, r = 0.0;
  for (int i = 0; i < x.n; ++i) {
    r += x_ref.value[i] * x_ref.value[i];
    const double er = x_ref.value[i] - x.value[i];
    e += er * er;
  }
  return std::sqrt(e / r);
}

int main() {
  for (int i = 0; i < 2; ++i) {
    // define our files
    std::string mat_file ="test_data/test_mat" + std::to_string(i + 1) + ".txt";
    std::string x_file = "test_data/test_x" + std::to_string(i + 1) + ".txt";
    std::string y_ref_file = "test_data/ref_y" + std::to_string(i + 1) + ".txt";
    std::string diag_ref_file =
        "test_data/ref_diag" + std::to_string(i + 1) + ".txt";

    std::cout << "\ncase " << i + 1 << '\n';

    std::cout << "\tloading vector data...\n\n";

    // load our vectors
    vec::DenseVec *x        = vec::create(utils::load_vec_size(x_file));
    vec::DenseVec *y_ref    = vec::create(utils::load_vec_size(y_ref_file));
    vec::DenseVec *diag_ref = vec::create(utils::load_vec_size(diag_ref_file));
    vec::DenseVec *buf      = vec::create(y_ref->n);

    utils::load_vec(x_file, *x);
    utils::load_vec(y_ref_file, *y_ref);
    utils::load_vec(diag_ref_file, *diag_ref);

    // create n and nnz
    int n, nnz;

    std::cout << "\tloading CSR matrix... " << mat_file << "\n";
    utils::load_mat_sizes(mat_file, n, nnz);

    csr::CSRMatrix *csr = csr::create(n, nnz);

    if (!csr) {
      std::cerr << "cannot create CSR for case " << i + 1 << '\n';
      return 1;
    }

    utils::load_csr(mat_file, *csr);

    std::cout << "\tcomputing y=Ax...\n";
    // dereference
    if (csr::mv(*csr, *x, *buf)) {
      std::cerr << "error occured in CSR mv for case " << i + 1 << '\n';
      return 1;
    }

    std::cout << "\tanalyzing the error...\n";
    double err = nrm2_error(*buf, *y_ref);
    if (err > 1e-12) {
      std::cerr << '\t' << FAIL;
    } else {
      std::cerr << '\t' << PASS;
    }
    std::cerr << " CSR mv test for case " << i + 1 << ", relative error is "
              << err << '\n';

    std::cout << "\textracting diagonal of CSR...\n";
    if (csr::extract_diag(*csr, *buf)) {
      std::cerr << "error occured in CSR extract_diag for case " << i + 1
                << '\n';
      return 1;
    }
    std::cout << "\tanalyzing the error...\n";
    err = nrm2_error(*buf, *diag_ref);
    if (err > 1e-12) {
      std::cerr << '\t' << FAIL;
    } else {
      std::cerr << '\t' << PASS;
    }
    std::cerr << " CSR extract_diag test for case " << i + 1
              << ", relative error is " << err << "\n\n";

    std::cout << "\tloading COO matrix...\n";
    coo::COOMatrix *coo = coo::create(n, nnz);
    if (!coo) {
      std::cerr << "cannot create COO for case " << i + 1 << '\n';
      return 1;
    }
    utils::load_coo(mat_file, *coo);

    std::cout << "\tcomputing y=Ax...\n";
    // dereference
    if (coo::mv(*coo, *x, *buf)) {
      std::cerr << "error occured in COO mv for case " << i + 1 << '\n';
      return 1;
    }

    std::cout << "\tanalyzing the error...\n";
    err = nrm2_error(*buf, *y_ref);
    if (err > 1e-12) {
      std::cerr << '\t' << FAIL;
    } else {
      std::cerr << '\t' << PASS;
    }
    std::cerr << " COO mv test for case " << i + 1 << ", relative error is "
              << err << '\n';

    std::cout << "\textracting diagonal of CSR...\n";
    if (coo::extract_diag(*coo, *buf)) {
      std::cerr << "error occured in OO extract_diag for case " << i + 1
                << '\n';
      return 1;
    }
    std::cout << "\tanalyzing the error...\n";
    err = nrm2_error(*buf, *diag_ref);
    if (err > 1e-12) {
      std::cerr << '\t' << FAIL;
    } else {
      std::cerr << '\t' << PASS;
    }
    std::cerr << " COO extract_diag test for case " << i + 1
              << ", relative error is " << err << "\n\n";

    std::cout << "\trelaxing memory...\n";

    // free memory
    vec::destroy(x);
    vec::destroy(y_ref);
    vec::destroy(diag_ref);
    vec::destroy(buf);

    // matrices
    csr::destroy(csr);
    coo::destroy(coo);
  }
  return 0;
}
