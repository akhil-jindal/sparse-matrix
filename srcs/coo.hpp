// This is part of AMS562 midterm project

/// \brief Coordinate sparse format

#ifndef _COO_HPP
#define _COO_HPP

// declaration
namespace vec {
struct DenseVec;
}

namespace coo {

/// \struct COOMatrix
/// \brief structure of csr representation
struct COOMatrix {
  double *v;  ///< value data array
  int *i;     ///< row indices
  int *j;     ///< column indices
  int n;      ///< size of the square matrix
  int nnz;    ///< total number of non-zeros
};

/// \brief create a csr matrix
/// \param[in] n row/column size of the squared matrix
/// \param[in] nnz total number of non-zeros
/// \return COO matrix pointer that points to the database
/// \sa destroy
COOMatrix *create(const int n, const int nnz);

/// \brief destroy a csr matrix
/// \param[in] mat coo matrix that is allocated by create_csr
void destroy(COOMatrix *mat);

/// \brief assign a triplet (i,j,v)
/// \param[out] mat coo matrix
/// \param[in] i row index
/// \param[in] j column index
/// \param[in] v value entry
/// \param[in] nnz_index array index of (i,j,v)
/// \return \a true if things go wrong, \a false ew
bool assign_ijv(COOMatrix &mat, const int i, const int j, const double v,
                const int nnz_index);

/// \brief extract the diagonal values
/// \param[in] A input coo matrix
/// \param[out] d diagonal entries
/// \return \a true if things go wrong, \a false ew
bool extract_diag(const COOMatrix &A, vec::DenseVec &diag);

/// \brief matrix vector multiplication
/// \param[in] A input coo matrix
/// \param[in] x input rhs vector
/// \param[out] y output lhs vector
/// \return  \a true if things go wrong, \a false ew
///
/// This function essentially is to compute y=A*x, where A is a squared matrix
/// and x is the rhs vector
bool mv(const COOMatrix &A, const vec::DenseVec &x, vec::DenseVec &y);

}  // namespace coo

#endif
