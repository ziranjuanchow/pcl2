/** \file eigen_matrix_impl.cpp
 * \brief Contains class definition for pcl2::core::EigenMatImpl
 */

#ifndef PCL2_EIGEN_MATRIX_IMPL_HPP
#define PCL2_EIGEN_MATRIX_IMPL_HPP

#include "pcl2/eigen_matrix_impl.h"
#include "pcl2/impl/matrix_view_impl.hpp"

template <typename T>
pcl2::core::EigenMatImpl<T>::EigenMatImpl () { assert (false); }

template <typename T>
pcl2::core::EigenMatImpl<T>::EigenMatImpl (const EigenMatImpl & f) { assert (false); }

template <typename T>
pcl2::core::EigenMatImpl<T>::EigenMatImpl (size_t rows, size_t cols) : 
  rows_ (rows), cols_ (cols), data_ (rows, cols)
{
}

template <typename T>
pcl2::core::MatImpl::Ptr 
pcl2::core::EigenMatImpl<T>::copy () const
{
  EigenMatImpl<T>::Ptr matrix_copy (new EigenMatImpl (rows_, cols_));
  matrix_copy->data_ = data_;
  return (matrix_copy);
}

template <typename T>
pcl2::core::MatImpl::Ptr 
pcl2::core::EigenMatImpl<T>::createNew (size_t i, size_t j) const
{
  return (Ptr (new EigenMatImpl (i, j)));
}

template <typename T>
pcl2::core::MatImpl::Ptr 
pcl2::core::EigenMatImpl<T>::createView (const TypedMatImpl<int>::ConstPtr & indices)
{
  return (MatImpl::Ptr (new MatViewImpl<T> (this->shared_from_this (), indices)));
}

template <typename T>
size_t 
pcl2::core::EigenMatImpl<T>::rows () const
{
  return (rows_);
}

template <typename T>
size_t 
pcl2::core::EigenMatImpl<T>::cols () const
{
  return (cols_);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::fill (const TypedMatImpl<T> & matrix)
{
  // Check to make sure the sizes are compatible
  /// \todo Replace these asserts with the appropriate if-statements and throws
  assert (matrix.rows () == rows_);
  assert (matrix.cols () == cols_);

  for (size_t j = 0; j < cols_; ++j)
    for (size_t i = 0; i < rows_; ++i)
      data_ (i, j) = matrix (i, j);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::fill (const T & value)
{
  // Assign the given value to every element of the data matrix
  data_ = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Constant(rows_, cols_, value);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator + (const T & operand) const
{
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  output->data_ = data_.array () + operand;
  return (output);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator - (const T & operand) const
{
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  output->data_ = data_.array () - operand;
  return (output);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator * (const T & operand) const
{
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  output->data_ = data_ * operand;
  return (output);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator / (const T & operand) const
{
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  output->data_ = data_ / operand;
  return (output);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator + (const TypedMatImpl<T> & operand) const
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      output->data_ (i, j) = data_ (i, j) + operand (i, j);
  return (output);
}

template <typename T>
typename pcl2::core::TypedMatImpl<T>::Ptr 
pcl2::core::EigenMatImpl<T>::operator - (const TypedMatImpl<T> & operand) const
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  Ptr output (new EigenMatImpl<T> (rows (), cols ()));
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      output->data_ (i, j) = data_ (i, j) - operand (i, j);
  return (output);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::operator += (const TypedMatImpl<T> & operand)
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      data_ (i, j) += operand (i, j);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::operator -= (const TypedMatImpl<T> & operand)
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      data_ (i, j) -= operand (i, j);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::operator *= (const TypedMatImpl<T> & operand)
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      data_ (i, j) *= operand (i, j);
}

template <typename T>
void 
pcl2::core::EigenMatImpl<T>::operator /= (const TypedMatImpl<T> & operand)
{
  assert (operand.rows () == rows ());
  assert (operand.cols () == cols ());
  for (size_t j = 0; j < cols (); ++j)
    for (size_t i = 0; i < rows (); ++i)
      data_ (i, j) /= operand (i, j);
}

template <typename T>
T & 
pcl2::core::EigenMatImpl<T>::operator () (size_t i, size_t j)
{
  return (data_ (i, j));
}

template <typename T>
const T & 
pcl2::core::EigenMatImpl<T>::operator () (size_t i, size_t j) const
{
  return (data_ (i, j));
}

#endif
