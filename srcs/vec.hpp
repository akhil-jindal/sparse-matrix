// This is part of AMS562 midterm project

/// \brief Dense vector interface

#ifndef _VEC_HPP
#define _VEC_HPP

namespace vec {

/// \struct DenseVec
/// \brief representation of dense vector
struct DenseVec {
  double *value;  ///< data array
  int n;          ///< length of the vector
};

/// \brief create a vector
/// \param[in] n size of the vector
/// \note The implementation is in vec.cpp
DenseVec *create(const int n);

/// \brief destroy a vector
/// \param[in] vec input vector
/// \note The implementation is in vec.cpp
void destroy(DenseVec *vec);

}  // namespace vec

#endif
