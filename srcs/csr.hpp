// This is part of AMS562 midterm project

/// \brief Compressed Sparse Row structure

#ifndef _CSR_HPP
#define _CSR_HPP

// declaration
namespace vec {
struct DenseVec;
}

namespace csr {

/// \struct CSRMatrix
/// \brief structure of csr representation
struct CSRMatrix {
  double *value;  ///< value data array
  int *indices;   ///< column indices array
  int *indptr;    ///< row pointer array
  int n;          ///< size of the square matrix
};

/// \brief create a csr matrix
/// \param[in] n row/column size of the squared matrix
/// \param[in] nnz non-zeros count
/// \return CSR matrix pointer that points to the database
/// \sa destroy_csr
CSRMatrix *create(const int n, const int nnz);

/// \brief destroy a csr matrix
/// \param[in] mat csr matrix that is allocated by create_csr
void destroy(CSRMatrix *mat);

/// \brief assign a row
/// \param[out] csr csr matrix
/// \param[in] row number of row in matrix
/// \param[in] cols column indice array corresponding to \a row
/// \param[in] vals corresponding values regarding \a cols
/// \param[in] nnz number of nonzeros
/// \return \a true if things go wrong, \a false ew
bool assign_row(CSRMatrix &mat, const int row, const int *cols,
                const double *vals, const int nnz);

/// \brief extract the diagonal values
/// \note A binary search implementation will gain you extra credits
/// \param[in] A input csr matrix
/// \param[out] d diagonal entries
/// \return \a true if things go wrong, \a false ew
bool extract_diag(const CSRMatrix &A, vec::DenseVec &diag);

/// \brief matrix vector multiplication
/// \param[in] A input csr matrix
/// \param[in] x input rhs vector
/// \param[out] y output lhs vector
/// \return  \a true if things go wrong, \a false ew
///
/// This function essentially is to compute y=A*x, where A is a squared matrix
/// and x is the rhs vector
bool mv(const CSRMatrix &A, const vec::DenseVec &x, vec::DenseVec &y);

}  // namespace csr

#endif
