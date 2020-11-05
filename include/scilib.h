#pragma once

#include <iostream>
#include <vector>

/**
 * TODO:
 * 
 **/

namespace scilib {
	template <typename T>
	class Matrix2d;
}

// Refactor scilib so that non-matrix2d are in their own?
namespace scilib {
	template <typename T>
	T median(const std::vector<T> &vecIn) noexcept;
	template <typename T>
	T mean(const std::vector<T> &vecIn) noexcept;
}

namespace scilib {
	template <typename T>
	T determinant(const Matrix2d<T> &matIn);
	template <typename T>
	Matrix2d<T> adjugate(const Matrix2d<T> &matIn);

	template <typename T>
	Matrix2d<T> median(const Matrix2d<T> &matIn, const int direction = 0) noexcept;
	template <typename T>
	Matrix2d<T> movmedian(const Matrix2d<T> &matIn, const int winSize, const int direction = 0) noexcept;
	template <typename T>
	Matrix2d<T> mean(const Matrix2d<T> &matIn, const int direction = 0) noexcept;
	template <typename T>
	Matrix2d<T> movmean(const Matrix2d<T> &matIn, const int winSize, const int direction) noexcept;

	template <typename T>
	Matrix2d<T> glm(const Matrix2d<T> &X, const Matrix2d<T> &Y) noexcept;
}

namespace scilib {
	template <typename T>
	Matrix2d<T> operator+(Matrix2d<T> lhs, const T &rhs);
	template <typename T>
	Matrix2d<T> operator+(const T &lhs, Matrix2d<T> rhs);
	template <typename T>
	Matrix2d<T> operator-(Matrix2d<T> lhs, const T &rhs);
	template <typename T>
	Matrix2d<T> operator-(const T &lhs, Matrix2d<T> rhs);
	template <typename T>
	Matrix2d<T> operator*(Matrix2d<T> lhs, const T &rhs);
	template <typename T>
	Matrix2d<T> operator*(const T &lhs, Matrix2d<T> rhs);
	template <typename T>
	Matrix2d<T> operator/(Matrix2d<T> lhs, const T &rhs);
	template <typename T>
	Matrix2d<T> operator/(const T &lhs, Matrix2d<T> rhs);
}

#include "scilib.hpp"