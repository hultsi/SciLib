#pragma once

#include <algorithm>

#include "fileSys.h"
#include "error.h"

#if DEBUG == 1	
	#define errMsg(msg) std::cerr << "Error in file " << __FILE__ << " at line " << __LINE__ << ":\n --- " << msg << "\n"
#else
	#define errMsg(msg)
#endif


namespace scilib {
	template <typename T>
	class Matrix2d {
		public:
		mutable std::vector<T> data;

		Matrix2d() {}
		Matrix2d(const int rows, const int cols) : rows(rows), cols(cols), size(rows*cols) {
			this->data.resize(size);
		}
		Matrix2d(const std::vector<T> &data, const int rows, const int cols) : data(data), rows(rows), cols(cols), size(rows*cols) {
			if (data.size() != (unsigned) this->size) {
				errMsg("Rows and/or columns don't match input vector size");
				this->rows = 0;
				this->cols = 0;
				this->size = 0;
				this->data.clear();
			}
		}
		Matrix2d(const fileSys::file<T> &file) : data(file.data), rows(file.rows), cols(file.columns), size(file.rows*file.columns) {
			if (data.size() != (unsigned) this->size) {
				errMsg("Rows and/or columns don't match input vector size");
				this->rows = 0;
				this->cols = 0;
				this->size = 0;
				this->data.clear();
			}
		}
		~Matrix2d() { 
			
		}

		auto begin() const { return this->data.begin(); }
		auto end() const { return this->data.end(); }

		void print() const {
			int i = 0;
			for (const T &el : this->data) {
				std::cout << el << "\t";
				++i;
				if (i == this->cols) {
					i = 0;
					std::cout << "\n";
				}
			}
		}

		void resize(int rows, int cols) {
			if (rows < 0 || cols < 0) {
				errMsg("Index out of bounds");
				return;
			}
			this->rows = rows;
			this->cols = cols;
			this->size = rows*cols;
			this->data.resize(this->size);
		}
		
		int getRows() const {
			return this->rows;
		}

		int getColumns() const {
			return this->cols;
		}

		void popRow(int row) {
			if (row < 0) return;
			this->data.erase(this->data.begin() + this->cols*row, this->data.begin() + (row+1)*this->cols);
			this->rows -= 1;
			this->size = this->rows*this->cols;
		}

		void popColumn(int col) {
			if (col < 0) return;
			int max = (this->cols - 1) * this->rows;
			for (int i = col; i < max; i += this->cols-1) {
				this->data.erase(this->data.begin()+i);
			}
			this->cols -= 1;
			this->size = this->rows*this->cols;
		}

		T &operator()(int ind) const {
			if (ind < 0 || ind > this->cols*this->rows) {
				errMsg("Index out of bounds. Returning (0,0).\n");
				return this->data.at(0);
			}
			return this->data.at(ind);
		}

		T &operator()(int row, int col) const {
			int ind = col + row*this->cols; 
			if (ind < 0 || ind > this->cols*this->rows) {
				errMsg("Index out of bounds. Returning (0,0).\n");
				return this->data.at(0);
			}
			return this->data.at(ind);
		}

		bool operator==(const Matrix2d<T> &matRight) const {
			if (matRight.getRows() != this->getRows())
				return false;
			else if (matRight.getColumns() != this->getColumns())
				return false;
			const T *elRight = &matRight.data.at(0);
			for (const T &el : *this)
				if (el != *elRight++)
					return false;
			return true;
		}

		Matrix2d<T> operator*(const Matrix2d<T> &matRight) const {
			Matrix2d<T> matOut;
			const int columns = this->cols;
			const int rows = matRight.rows;
			if (columns != rows) {
				errMsg("Left matrix columns != right matrix rows\n");
				return matOut;
			}
			matOut.resize(this->rows, matRight.cols);
			int offset1 = 0;
			int offset2 = 0;
			for (T &el : matOut) {
				T *val1 = &this->data.at(offset1);
				T *val2 = &matRight.data.at(offset2);
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

		Matrix2d<T> operator~() const {
			Matrix2d<T> matOut(this->cols, this->rows);
			int offset = 0;
			int row = 0;
			T *val = nullptr;
			for (T &el : this->data) {
				if (row % matOut.rows == 0) {
					val = &matOut.data.at(offset++);
					row = 0;
				}
				*(val + row*matOut.cols) = el;
				++row;
			}
			return matOut;
		}

		Matrix2d<T> operator!() const {
			if (this->getRows() != this->getColumns()) {
				std::cerr << "Non square matrix is not invertible\n";
				return *this;
			}
			Matrix2d<T> matOut(this->rows, this->cols);
			if (matOut.getRows() == 1) {
				matOut(0,0) = 1/this->data.at(0);
			} else {
				T det = scilib::determinant(*this);
				if (std::abs(det) < 1e-15) {
					errMsg("Matrix is close to singular");
					return matOut;
				}

				Matrix2d<T> adj = scilib::adjugate(*this);
				T *val = &matOut.data.at(0);
				for (T &a : adj) {
					*val++ = a/det;
				}
			}
			return matOut;
		}

		private:
		int rows = 0;
		int cols = 0;
		int size = 0;
	};
}

namespace scilib {
	template <typename T>
	T median(const std::vector<T> &vecIn) noexcept {
		std::vector<T> tmpVec = vecIn;
		const int length = tmpVec.size();
		if (length % 2 == 0) {
			const int halfLen = length/2;
			std::nth_element(tmpVec.begin(), tmpVec.begin() + halfLen, tmpVec.end());
			std::nth_element(tmpVec.begin(), tmpVec.begin() + halfLen - 1, tmpVec.end());
			return (tmpVec.at(halfLen) + tmpVec.at(halfLen-1)) / 2;
		} else {
			const int halfLen = (length+1)/2-1;
			std::nth_element(tmpVec.begin(), tmpVec.begin() + halfLen, tmpVec.end());
			return tmpVec.at(halfLen);
		}
	}

	template <typename T>
	T mean(const std::vector<T> &vecIn) noexcept {
		std::vector<T> vecOut;
		T sum = 0;
		for (const T &el : vecIn)
			sum += el;
		return (sum/(vecIn.size()));
	}
}

namespace scilib {
	// Make this return Matrix2d
	template <typename T>
	T determinant(const Matrix2d<T> &dataMat) {
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

	template <typename T>
	Matrix2d<T> adjugate(const Matrix2d<T> &matIn) {
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
	Matrix2d<T> median(const Matrix2d<T> &matIn, const int direction) noexcept {
		Matrix2d<T> matOut;
		Matrix2d<T> tmpMat = matIn;
		int length = 0;
		if (direction == 0) {
			length = tmpMat.getRows()*tmpMat.getColumns();
			matOut.resize(1,1);
			if (length % 2 == 0) {
				const int halfLen = length/2;
				std::nth_element(tmpMat.begin(), tmpMat.begin() + halfLen, tmpMat.end());
				std::nth_element(tmpMat.begin(), tmpMat.begin() + halfLen - 1, tmpMat.end());
				matOut.data.at(0) = (tmpMat.data.at(halfLen) + tmpMat.data.at(halfLen-1)) / 2;
			} else {
				const int halfLen = (length+1)/2-1;
				std::nth_element(tmpMat.begin(), tmpMat.begin() + halfLen, tmpMat.end());
				matOut.data.at(0) = tmpMat.data.at(halfLen);
			}
			return matOut;
		} else if (direction == 1) {
			length = tmpMat.getRows();
			matOut.resize(1, matIn.getColumns());
			tmpMat = ~tmpMat;
		} else if (direction == 2) {
			length = tmpMat.getColumns();
			matOut.resize(matIn.getRows(), 1);
		} else {
			return matOut;
		}
		int pos = 0;
		int ind = 0;
		if (length % 2 == 0) {
			const int halfLen = length/2;
			for (T &el : matOut) {
				std::nth_element(tmpMat.begin() + pos, tmpMat.begin() + halfLen + pos, tmpMat.begin() + tmpMat.getColumns() + pos);
				std::nth_element(tmpMat.begin() + pos, tmpMat.begin() + halfLen - 1 + pos, tmpMat.begin() + tmpMat.getColumns() + pos);
				matOut.data.at(ind) = (tmpMat.data.at(halfLen+pos) + tmpMat.data.at(halfLen-1+pos)) / 2;
				++ind;
				pos += tmpMat.getColumns();
			}
		} else {
			const int halfLen = (length+1)/2-1;
			for (T &el : matOut) {
				std::nth_element(tmpMat.begin() + pos, tmpMat.begin() + halfLen + pos, tmpMat.begin() + tmpMat.getColumns() + pos);
				matOut.data.at(ind) = tmpMat.data.at(halfLen+pos);
				++ind;
				pos += tmpMat.getColumns();
			}
		}
		return matOut;
	}

	template <typename T>
	Matrix2d<T> movmedian(const Matrix2d<T> &matIn, const int winSize, const int direction) noexcept {
		const int rows = matIn.getRows();
		const int columns = matIn.getColumns();
		const int size = rows*columns;
		Matrix2d<T> matOut = matIn; //(rows,columns);
		if (winSize < 1)
			return matOut;
		
		const int ws = winSize + ((winSize+1) % 2); // Make sure winSize == odd
		const int winHalf = (ws+1)/2 - 1;
		int pos = 0;
		int posLeft = -winHalf;
		int posRight = winHalf+1;
		if (direction == 0) {
			if (winSize > matOut.getColumns()*matOut.getRows())
				return matOut;
			for (T &el : matOut) {
				if (pos < winHalf) {
					std::vector<T> tmp(matIn.data.begin(), matIn.data.begin()+posRight);
					el = scilib::median(tmp);
				} else if (pos > size-winHalf-1) {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+size);
					el = scilib::median(tmp);
				} else {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+posRight);
					el = scilib::median(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
		} else if (direction == 1) {
			if (winSize > matOut.getRows())
				return matOut;
			Matrix2d<T> tmpMat = ~matIn; // TODO: use indexing instead of transpose
			int posMod = 0;
			for (T &el : matOut) {
				posMod = pos % tmpMat.getColumns();
				if (posMod < winHalf) {
					std::vector<T> tmp(tmpMat.data.begin() + pos - posMod, tmpMat.data.begin() + posRight);
					el = scilib::median(tmp);
				} else if (posMod > tmpMat.getColumns()-winHalf-1) {
					std::vector<T> tmp(tmpMat.data.begin() + posLeft, tmpMat.data.begin() + pos + (tmpMat.getColumns() - posMod));
					el = scilib::median(tmp);
				} else {
					std::vector<T> tmp(tmpMat.data.begin()+posLeft, tmpMat.data.begin()+posRight);
					el = scilib::median(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
			matOut = ~matOut;
		} else if (direction == 2) {
			if (winSize > matOut.getColumns())
				return matOut;
			int posMod = 0;
			for (T &el : matOut) {
				posMod = pos % matIn.getColumns();
				if (posMod < winHalf) {
					std::vector<T> tmp(matIn.data.begin() + pos - posMod, matIn.data.begin() + posRight);
					el = scilib::median(tmp);
				} else if (posMod > matIn.getColumns()-winHalf-1) {
					std::vector<T> tmp(matIn.data.begin() + posLeft, matIn.data.begin() + pos + (matIn.getColumns() - posMod));
					el = scilib::median(tmp);
				} else {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+posRight);
					el = scilib::median(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
		}
		return matOut;
	}

	template <typename T>
	Matrix2d<T> mean(const Matrix2d<T> &matIn, const int direction) noexcept {
		Matrix2d<T> matOut;
		const int rows = matIn.getRows();
		const int cols = matIn.getColumns();
		if (direction == 0) {	
			T sum = 0;
			for (const T &el : matIn.data)
				sum += el;
			matOut.data.emplace_back(sum/(rows*cols));
		} else if (direction == 1) {
			matOut.resize(1,cols);
			int col = 0;
			for (T &el : matOut) {
				for (int row = 0; row < rows; ++row) {
					el += matIn(row,col)/rows;
				}
				++col;
			}
		} else if (direction == 2) {
			matOut.resize(rows,1);
			int row = 0;
			for (T &el : matOut) {
				for (int col = 0; col < cols; ++col) {
					el += matIn(row,col)/cols;
				}
				++row;
			}
		}
		return matOut;
	}

	template <typename T>
	Matrix2d<T> movmean(const Matrix2d<T> &matIn, const int winSize, const int direction) noexcept {
		const int rows = matIn.getRows();
		const int columns = matIn.getColumns();
		const int size = rows*columns;
		Matrix2d<T> matOut = matIn; //(rows,columns);
		if (winSize < 1)
			return matOut;
		
		const int ws = winSize + ((winSize+1) % 2); // Make sure winSize == odd
		const int winHalf = (ws+1)/2 - 1;
		int pos = 0;
		int posLeft = -winHalf;
		int posRight = winHalf+1;
		if (direction == 0) {
			if (winSize > matOut.getColumns()*matOut.getRows())
				return matOut;
			for (T &el : matOut) {
				if (pos < winHalf) {
					std::vector<T> tmp(matIn.data.begin(), matIn.data.begin()+posRight);
					el = scilib::mean(tmp);
				} else if (pos > size-winHalf-1) {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+size);
					el = scilib::mean(tmp);
				} else {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+posRight);
					el = scilib::mean(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
		} else if (direction == 1) {
			if (winSize > matOut.getRows())
				return matOut;
			Matrix2d<T> tmpMat = ~matIn; // TODO: use indexing instead of transpose
			int posMod = 0;
			for (T &el : matOut) {
				posMod = pos % tmpMat.getColumns();
				if (posMod < winHalf) {
					std::vector<T> tmp(tmpMat.data.begin() + pos - posMod, tmpMat.data.begin() + posRight);
					el = scilib::mean(tmp);
				} else if (posMod > tmpMat.getColumns()-winHalf-1) {
					std::vector<T> tmp(tmpMat.data.begin() + posLeft, tmpMat.data.begin() + pos + (tmpMat.getColumns() - posMod));
					el = scilib::mean(tmp);
				} else {
					std::vector<T> tmp(tmpMat.data.begin()+posLeft, tmpMat.data.begin()+posRight);
					el = scilib::mean(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
			matOut = ~matOut;
		} else if (direction == 2) {
			if (winSize > matOut.getColumns())
				return matOut;
			int posMod = 0;
			for (T &el : matOut) {
				posMod = pos % matIn.getColumns();
				if (posMod < winHalf) {
					std::vector<T> tmp(matIn.data.begin() + pos - posMod, matIn.data.begin() + posRight);
					el = scilib::mean(tmp);
				} else if (posMod > matIn.getColumns()-winHalf-1) {
					std::vector<T> tmp(matIn.data.begin() + posLeft, matIn.data.begin() + pos + (matIn.getColumns() - posMod));
					el = scilib::mean(tmp);
				} else {
					std::vector<T> tmp(matIn.data.begin()+posLeft, matIn.data.begin()+posRight);
					el = scilib::mean(tmp);
				}
				++pos;
				++posLeft;
				++posRight;
			}
		}
		return matOut;
	}

	template <typename T>
	Matrix2d<T> glm(const Matrix2d<T> &X, const Matrix2d<T> &Y) noexcept {
		if (X.getRows() != Y.getRows())
			return Matrix2d<T>();
		return (!(~X*X))*(~X)*Y;
	}

	// TODO: implement weighted regression
	// template <typename T>
	// Matrix2d<T> glm(const Matrix2d<T> &X, const Matrix2d<T> &Y, const Matrix2d<T> &W) noexcept {
	// 	if (X.getRows() != Y.getRows())
	// 		return Matrix2d<T>();
	// 	return (!(~X*X))*(~X)*Y;
	// }
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
