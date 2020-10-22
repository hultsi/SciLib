#pragma once

#include "fileSys.h"

namespace scilib {
	template <typename T>
	class Matrix2d {
		public:
		std::vector<T> mat;

		Matrix2d() {}
		Matrix2d(const int rows, const int cols) {
			this->rows = rows;
			this->cols = cols;
			this->mat.resize(rows*cols,0);
		}
		Matrix2d(const int rows, const int cols, std::vector<T> &mat) {
			int mod = rows % mat.size();
			if (mod != 0) {
				std::cerr << "Rows and/or columns don't match input vector size\n";
				return;
			}
			this->rows = rows;
			this->cols = cols;
			this->mat.resize(rows*cols);
			int *val = &mat.at(0);
			for (T &el : this->mat)
				el = *val++;
		}
		Matrix2d(fileSys::file<T> &file) {
			int mod = file.data.size() % file.rows;
			if (mod != 0) {
				std::cerr << "Rows and/or columns don't match input vector size\n";
				return;
			}
			this->rows = file.rows;
			this->cols = file.columns;
			this->mat.resize(file.rows * file.columns);
			T *val = &file.data.at(0);
			for (T &el : this->mat)
				el = *val++;
		}
		~Matrix2d() { 
			
		}

		auto begin() { return this->mat.begin(); }
		auto end() { return this->mat.end(); }

		void print() {
			int i = 0;
			for (const T &el : this->mat) {
				std::cout << el << "\t";
				++i;
				if (i == this->cols) {
					i = 0;
					std::cout << "\n";
				}
			}
		}

		void resize(int rows, int cols) {
			this->rows = rows;
			this->cols = cols;
			this->mat.resize(rows*cols,0);
		}
		
		int getRows() {
			return this->rows;
		}

		int getColumns() {
			return this->cols;
		}

		void popRow(int row) {
			this->mat.erase(this->mat.begin() + this->cols*(row-1), this->mat.begin() + row*this->cols);
			this->rows -= 1;
		}

		void popColumn(int col) {
			int max = (this->cols - 1) * this->rows;
			for (int i = col; i < max; i += this->cols-1) {
				this->mat.erase(this->mat.begin()+i);
			}
			this->cols -= 1;
		}

		T &operator()(int row, int col) noexcept {
			int pos = col + row*this->cols;
			if (pos < 0 || pos > this->cols*this->rows) {
				std::cout << "Warning: Index " << pos << " out of bounds. Returning end().\n";
				return *this->mat.end();
			}
			return this->mat.at(col + row*this->cols);
		}

		Matrix2d<T> operator*(Matrix2d<T> &matRight) {
			Matrix2d<T> matOut;
			const int columns = this->cols;
			const int rows = matRight.rows;
			if (columns != rows) {
				std::cerr << "Left matrix columns != right matrix rows, " << columns << " != " << rows << "\n";
				return matOut;
			}
			matOut.resize(this->rows, matRight.cols);
			int offset1 = 0;
			int offset2 = 0;
			for (T &el : matOut) {
				T *val1 = &this->mat.at(offset1);
				T *val2 = &matRight.mat.at(offset2);
				for (int i = 0; i < columns; ++i) {
					el += *(val1++) * *(val2);
					val2 += matRight.cols;
				}
				offset2 += 1;
				if (offset2 == matRight.cols) {
					offset1 += this->cols;
					offset2 = 0;
				}
			}
			return matOut;
		}

		Matrix2d<T> operator~() {
			Matrix2d<T> matOut(this->cols, this->rows);
			int offset = 0;
			int row = 0;
			T *val = nullptr;
			for (T &el : this->mat) {
				if (row % matOut.rows == 0) {
					val = &matOut.mat.at(offset++);
					row = 0;
				}
				*(val + row*matOut.cols) = el;
				++row;
			}
			return matOut;
		}


		private:
		int rows = 0;
		int cols = 0;
	};
}

namespace scilib {
	// TODO: Optimize with pointers instead of using popRow, popCol
	template <typename T>
	T determinant(Matrix2d<T> &dataMat, T *P) {
		if (P == nullptr) {
			P = &dataMat.mat.at(0);
		}
		int det = 0;
		int sign = 1;
		for (int i = 0; i < dataMat.getColumns(); ++i) {
			det += sign * (*P) * determinant(dataMat, P + dataMat.getColumns()+1);
			sign *= -1;
		}
		return det;
	}
}

namespace scilib {
	template <typename T, typename H>
	Matrix2d<T> operator+(Matrix2d<T> lhs, const H &rhs) {
		for (T &el : lhs)
			el += rhs;
		return lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator+(const H &lhs, Matrix2d<T> rhs) {
		return rhs+lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator-(Matrix2d<T> lhs, const H &rhs) {
		for (T &el : lhs)
			el -= rhs;
		return lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator-(const H &lhs, Matrix2d<T> rhs) {
		for (T &el : rhs)
			el = lhs-el;
		return rhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator*(Matrix2d<T> lhs, const H &rhs) {
		for (T &el : lhs)
			el *= rhs;
		return lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator*(const H &lhs, Matrix2d<T> rhs) {
		return rhs*lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator/(Matrix2d<T> lhs, const H &rhs) {
		for (T &el : lhs)
			el /= rhs;
		return lhs;
	}
	template <typename T, typename H>
	Matrix2d<T> operator/(const H &lhs, Matrix2d<T> rhs) {
		for (T &el : rhs)
			el = lhs/el;
		return rhs;
	}
}
