#pragma once

#include <algorithm>

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
			int mod = mat.size() % rows;
			if (mod != 0) {
				std::cerr << "Rows and/or columns don't match input vector size\n";
				return;
			}
			this->rows = rows;
			this->cols = cols;
			this->mat.resize(rows*cols);
			T *val = &mat.at(0);
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

		void print() const {
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
		
		int getRows() const {
			return this->rows;
		}

		int getColumns() const {
			return this->cols;
		}

		void popRow(int row) {
			this->mat.erase(this->mat.begin() + this->cols*row, this->mat.begin() + (row+1)*this->cols);
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

		// TODO: optimize this. E.g., remove matOut and return matRight.
		Matrix2d<T> operator*(Matrix2d<T> matRight) {
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

		Matrix2d<T> operator!() {
			if (this->getRows() != this->getColumns()) {
				std::cerr << "Non square matrix is not invertible\n";
				return *this;
			}
			Matrix2d<T> matOut(this->rows, this->cols);
			if (matOut.getRows() == 1) {
				matOut(0,0) = 1/this->mat.at(0);
			} else {
				T det = scilib::determinant(*this);
				Matrix2d<T> adj = scilib::adjugate(*this);
				T *val = &matOut.mat.at(0);
				for (T &a : adj) {
					*val++ = a/det;
				}
			}
			return matOut;
		}

		private:
		int rows = 0;
		int cols = 0;
	};
}

namespace scilib {
	template <typename T>
	T determinant(Matrix2d<T> &dataMat) {
		if (dataMat.getRows() != dataMat.getColumns()) {
			std::cerr << "Non square matrix is not invertible\n";
			return 0;
		}
		if (dataMat.getColumns() == 1) {
			return dataMat(0,0);
		}
		T det = 0;
		int sign = 1;
		int max = dataMat.getColumns();
		for (int i = 0; i < max; ++i) {
			Matrix2d<T> tmpMat = dataMat;
			tmpMat.popRow(0);
			tmpMat.popColumn(i);
			det += sign * dataMat(0,i) * determinant(tmpMat);
			sign *= -1;
		}
		return det;
	}
	// This did not work btw.
	// template <typename T>
	// T determinant(Matrix2d<T> &matIn) {
	// 	if (matIn.getRows() != matIn.getColumns()) {
	// 		std::cerr << "Cannot calculate determinant of a non square matrix\n";
	// 		return 0;
	// 	}
	// 	if (matIn.getRows() == 1)
	// 		return matIn(0,0);
	// 	else if (matIn.getRows() == 2)
	// 		return matIn(0,0)*matIn(1,1) - matIn(0,1)*matIn(1,0);
	// 	int det = 0;
	// 	int rows = matIn.getRows();
	// 	int cols = matIn.getColumns();
	// 	int pos = 1;
	// 	int tmp = 0;
	// 	for (int i = 0; i < cols; ++i) {
	// 		tmp = matIn(0,i);
	// 		pos = i+1;
	// 		for (int k = 1; k < rows; ++k) {
	// 			if (pos == cols) {
	// 				pos = 0;
	// 				tmp *= matIn(k, pos); 
	// 			} else {
	// 				tmp *= matIn(k, pos); 
	// 			}
	// 			++pos;
	// 		}
	// 		det += tmp;
	// 	}
	// 	for (int i = 0; i < cols; ++i) {
	// 		tmp = matIn(0,i);
	// 		pos = i-1;
	// 		for (int k = 1; k < rows; ++k) {
	// 			if (pos == -1) {
	// 				pos = cols-1;
	// 				tmp *= matIn(k, pos); 
	// 			} else {
	// 				tmp *= matIn(k, pos); 
	// 			}
	// 			--pos;
	// 		}
	// 		det -= tmp;
	// 	}
	// 	return det;
	// }

	template <typename T>
	Matrix2d<T> adjugate(Matrix2d<T> &matIn) {
		if (matIn.getRows() != matIn.getColumns()) {
			std::cerr << "Non square matrix is not invertible\n";
			return matIn;
		}
		const int rows = matIn.getRows();
		const int cols = matIn.getColumns();
		Matrix2d<T> matOut(rows, cols);

		Matrix2d<T> tmpMat = matIn;
		int currentRow = 0;
		int currentCol = 0;
		int sign = 1;
		for (T &el: matOut) {
			tmpMat = matIn;
			tmpMat.popRow(currentRow);
			tmpMat.popColumn(currentCol);
			sign = ((currentRow+currentCol+1) % 2)*2 - 1;
			el = sign*determinant(tmpMat);
			++currentCol;
			if (currentCol == cols) {
				currentCol = 0;
				++currentRow;
			}
		}

		return ~matOut;
	}

	template <typename T>
	T median(std::vector<T> v) noexcept {
		const int length = v.size();
		if (length % 2 == 0) {
			const int halfLen = length/2;
			std::nth_element(v.begin(), v.begin() + halfLen, v.end());
			std::nth_element(v.begin(), v.begin() + halfLen - 1, v.end());
			return (v.at(halfLen) + v.at(halfLen-1)) / 2;
		} else {
			const int halfLen = (length+1)/2-1;
			std::nth_element(v.begin(), v.begin() + halfLen, v.end());
			return v.at(halfLen);
		}
	}
	template <typename T>
	T median(Matrix2d<T> &inMat) noexcept {
		return median(inMat.mat);
	}

	template <typename T>
	std::vector<T> movmedian(const std::vector<T> &v, int winSize) noexcept {
		std::vector<T> vOut = v;
		winSize = winSize + ((winSize+1) % 2);
		const int length = v.size();
		const int winHalf = (winSize+1)/2 - 1;
		int pos = 0;
		int posLeft = -winHalf;
		int posRight = winHalf+1;
		for (T &el : vOut) {
			if (pos < winHalf) {
				std::vector<T> tmp(v.begin(), v.begin()+posRight);
				el = median(tmp);
			} else if (pos > length-winHalf-1) {
				std::vector<T> tmp(v.begin()+posLeft, v.begin()+length);
				el = median(tmp);
			} else {
				std::vector<T> tmp(v.begin()+posLeft, v.begin()+posRight);
				el = median(tmp);
			}
			++pos;
			++posLeft;
			++posRight;
		}
		return vOut;
	}
	template <typename T>
	Matrix2d<T> movmedian(const Matrix2d<T> &matIn, int winSize) noexcept {
		std::vector<T> tmp = movmedian(matIn.mat, winSize);
		Matrix2d<T> matOut(matIn.getRows(), matIn.getColumns(), tmp);
		return matOut;
	}

	template <typename T>
	Matrix2d<T> glm(Matrix2d<T> &X, Matrix2d<T> &Y) noexcept {
		if (X.getRows() != Y.getRows())
			return Matrix2d<T>();
		return (!(~X*X))*(~X)*Y;
	}
}

namespace scilib {
	template <typename T>
	Matrix2d<T> operator+(Matrix2d<T> lhs, const T &rhs) {
		for (T &el : lhs)
			el += rhs;
		return lhs;
	}
	template <typename T>
	Matrix2d<T> operator+(const T &lhs, Matrix2d<T> rhs) {
		return rhs+lhs;
	}
	template <typename T>
	Matrix2d<T> operator-(Matrix2d<T> lhs, const T &rhs) {
		for (T &el : lhs)
			el -= rhs;
		return lhs;
	}
	template <typename T>
	Matrix2d<T> operator-(const T &lhs, Matrix2d<T> rhs) {
		for (T &el : rhs)
			el = lhs-el;
		return rhs;
	}
	template <typename T>
	Matrix2d<T> operator*(Matrix2d<T> lhs, const T &rhs) {
		for (T &el : lhs)
			el *= rhs;
		return lhs;
	}
	template <typename T>
	Matrix2d<T> operator*(const T &lhs, Matrix2d<T> rhs) {
		return rhs*lhs;
	}
	template <typename T>
	Matrix2d<T> operator/(Matrix2d<T> lhs, const T &rhs) {
		for (T &el : lhs)
			el /= rhs;
		return lhs;
	}
	template <typename T>
	Matrix2d<T> operator/(const T &lhs, Matrix2d<T> rhs) {
		for (T &el : rhs)
			el = lhs/el;
		return rhs;
	}
}
