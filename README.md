### SciLib

Library for matrix manipulation, modeling etc. At the moment the library includes 2 namespaces, fileSys and scilib.
	- fileSys is used for loading/saving files from/to hard drive
	- scilib is used for matrix manipulations etc.

```C++
namespace scilib {
	// Class specific functionalities below
	template <typename T>
	class Matrix2d;

	// Calculates Matrix2d determinant
	template <typename T>
	T determinant(Matrix2d<T> &matIn);
	// Calculates Matrix2d adjugate
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

	// Overloaded operators for Matrix2d +,-,*,/ (int/double/etc.)
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
```

```C++
template <typename T>
class scilib::Matrix2d {
	public:
		// Matrix data
		std::vector<T> mat;
		// Constructors/Destructors
		Matrix2d();
		Matrix2d(const int rows, const int cols);
		Matrix2d(const int rows, const int cols, std::vector<T> &mat);
		Matrix2d(fileSys::file<T> &file);
		~Matrix2d();
		// Iterators for the vector holding the matrix values
		auto begin() { return this->mat.begin(); }
		auto end() { return this->mat.end(); }
		// Print contents of the matrix
		void print();
		// Resize matrix and init with values of 0
		void resize(int rows, int cols);
		// Get number of rows in the matrix currently
		int getRows();
		// Get number of columns in the matrix currently
		int getColumns();
		// Remove row from the matrix
		void popRow(int row);
		// Remove column from the matrix
		void popColumn(int col);
		// Operator to select element from the matrix at (row,col)
		T &operator()(int row, int col) noexcept;
		// Matrix product
		Matrix2d<T> operator*(Matrix2d<T> &matRight);
		// Matrix transpose operator
		Matrix2d<T> operator~();
		// Matrix inverse operator
		Matrix2d<T> operator!();
}
```

```C++
namespace fileSys {
	template <typename T>
	struct file;
	
	template <typename T>
	bool readFile(std::vector<std::string> &dataVec, const T path, const char delim = '\t');
	template <typename T>
	bool readFile(file<std::string> &dataStruct, const T path, const char delim = '\t');
	template <typename T>
	bool readFile(file<double> &dataStruct, const T path, const char delim = '\t');
}
```