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

namespace scilib {
	template <typename T>
	T determinant(const Matrix2d<T> &matIn);
	template <typename T>
	Matrix2d<T> adjugate(const Matrix2d<T> &matIn);

	template <typename T>
	T median(const std::vector<T> &vec) noexcept; 
	template <typename T>
	T median(const Matrix2d<T> &matIn) noexcept;
	template <typename T>
	std::vector<T> movmedian(const std::vector<T> &v, int winSize) noexcept; 
	template <typename T>
	Matrix2d<T> movmedian(const Matrix2d<T> &matIn, int winSize) noexcept;
	// template <typename T>
	// T mean(std::vector<T> v) noexcept; 
	template <typename T>
	Matrix2d<T> mean(const Matrix2d<T> &matIn, const int direction = 0) noexcept;
	
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