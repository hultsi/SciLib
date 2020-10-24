#pragma once

#include <iostream>
#include <vector>

/**
 * --- scilib::Matrix2d ---
 * public:
 * 		Matrix2d(const int rows, const int cols)
 *		Matrix2d(const int rows, const int cols, std::vector<T> &mat)
 * 		Matrix2d(fileSys::file<T> &file)
 * 		~Matrix2d()
 * 		auto begin()
 * 		auto end()
 * 
 * - Select matrix element using bracket notation mat(row,col)
 * 		T &operator()(int row, int col) noexcept
 * 
 * - Matrix product
 * 		Matrix2d<T> operator*(Matrix2d<T> &matLeft, Matrix2d<T> &matRight)
 * 
 * - Matrix transpose
 * 		Matrix2d<T> operator~()
 * - 
 * private:
 *		int rows = 0;
 *		int cols = 0;
 *		int size = 0;
 *
 * --- scilib ---
 * - Returns input matrix determinant
 * 		template <typename T>
 *  	T scilib::determinant(Matrix2d<T> mat);
 **/
namespace scilib {
	template <typename T>
	class Matrix2d;
}

namespace scilib {
	template <typename T>
	T determinant(Matrix2d<T> &matIn);
	template <typename T>
	Matrix2d<T> adjugate(Matrix2d<T> &matIn);

	template <typename T>
	T median(std::vector<T> &v) noexcept; 
	template <typename T>
	T median(Matrix2d<T> &matIn) noexcept;
	template <typename T>
	std::vector<T> movmedian(std::vector<T> &v, int winSize); 
	template <typename T>
	Matrix2d<T> movmedian(Matrix2d<T> &matIn, int winSize);
}

namespace scilib {
	template <typename T, typename H>
	Matrix2d<T> operator+(Matrix2d<T> lhs, const H &rhs);
	template <typename T, typename H>
	Matrix2d<T> operator+(const H &lhs, Matrix2d<T> rhs);
	template <typename T, typename H>
	Matrix2d<T> operator-(Matrix2d<T> lhs, const H &rhs);
	template <typename T, typename H>
	Matrix2d<T> operator-(const H &lhs, Matrix2d<T> rhs);
	template <typename T, typename H>
	Matrix2d<T> operator*(Matrix2d<T> lhs, const H &rhs);
	template <typename T, typename H>
	Matrix2d<T> operator*(const H &lhs, Matrix2d<T> rhs);
	template <typename T, typename H>
	Matrix2d<T> operator/(Matrix2d<T> lhs, const H &rhs);
	template <typename T, typename H>
	Matrix2d<T> operator/(const H &lhs, Matrix2d<T> rhs);
}
#include "scilib.hpp"