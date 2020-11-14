# **SciLib**

Library for matrix manipulation, modeling etc. At the moment the library includes 2 namespaces, fileSys and scilib.

## Includes
- ## fileSys.h
	- Used for reading and loading data from from/to hard drive
- ## scilib.h
	- Contains the Matrix2d class and functions for manipulating it

# Documentation

## <span style="font-size: 28px">**fileSys.h**</span>

## **Contains**

- <span style="font-size: 18px">struct file< T ></span>
- <span style="font-size: 18px">bool readFile< T >(file std::string, const T, const char)</span>

</br>

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px">struct fileSys::file< T ></span>

```C++
template <typename T>
struct fileSys::file {
	std::vector<T> data;
	int rows = 0;
	int columns = 0;
};
```

Used to load data files into memory within a 1 dimensional vector while also preserving the knowledge of the rows and columns within the loaded data file. This can be used to initialize matrix::Matrix2d< T >.</br>

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px">bool fileSys::readFile< T >()</span>

```C++
template <typename T>
bool readFile(file<std::string> &dataStruct, const T path, const char delim = '\t');
template <typename T>
bool readFile(file<int> &dataStruct, const T path, const char delim = '\t');
template <typename T>
bool readFile(file<float> &dataStruct, const T path, const char delim = '\t');
template <typename T>
bool readFile(file<double> &dataStruct, const T path, const char delim = '\t');
```

Used to load text file from specified path to an std::vector within fileSys::file.
- **dataStruct** is a reference to the fileSys::file struct where the data is saved into
- **path** is the path to the text file
- **delim** is the delimiter used in the text file

</br>

## <span style="font-size: 28px">**scilib.h**</span>

## **Contains**
- <span style="font-size: 18px">class Matrix2d< T ></span>
- <span style="font-size: 18px">functions</span>

<br>

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px;">class scilib::Matrix2d< T ></span>

```C++
template <typename T>
class Matrix2d;
```

<p>The matrix class of the library. Basic element by element operations like summing, subtracting and dividing are included in the class. Calculating element by element product is done via the Matrix2d::dot() function since the * operator calculates matrix product.</p><br>

```C++
void scilib::Matrix2d<T>::print() const
```

<p>Prints the matrix content.</p><br>

```C++
void scilib::Matrix2d<T>::resize(int rows, int cols)
```

<p>Resizes the matrix.</p><br>

```C++
int scilib::Matrix2d<T>::getRows() const
```

<p>Returns the amount of rows in the matrix.</p><br>

```C++
int scilib::Matrix2d<T>::getColumns() const
```

<p>Returns the amount of columns in the matrix.</p><br>

```C++
void scilib::Matrix2d<T>::popRow(int row)
```

<p>Removes a row from the matrix.</p><br>

```C++
void scilib::Matrix2d<T>::popColumn(int col)
```

<p>Removes a column from the matrix.</p><br>

```C++
T scilib::Matrix2d<T>::&operator()(int ind) const
```

<p>Returns a reference to the matrix element in the position "ind" calculated column-wise. Essentially gives you a simple interface to access the std::vector data which contains the matrix data.</p><br>

```C++
T scilib::Matrix2d<T>::&operator()(int row, int col) const
```

<p>Returns a reference to the matrix element in the given row-column position.</p><br>

```C++
bool scilib::Matrix2d<T>::operator==(const Matrix2d<T> &matRight) const 
```

<p>Comparison operator for matrices. Returns true if each element Matrix1(a,b) matches Matrix2(a,b).</p><br>

```C++
Matrix2d<T> scilib::Matrix2d<T>::operator*(const Matrix2d<T> &matRight) const
```

<p>Calculates matrix product and returns a new matrix holding the values.</p><br>

```C++
Matrix2d<T> scilib::Matrix2d<T>::operator~() const
```

<p>Calculates matrix transpose and returns the transposed matrix.</p><br>

```C++
Matrix2d<T> scilib::Matrix2d<T>::operator!() const
```

<p>Calculates matrix inverse and returns the inversed matrix.</p><br>

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px">Functions</span>

```C++
template <typename T>
T determinant(const Matrix2d<T> &matIn)
```

<p>Calculates determinant of the input matrix.</p><br>

```C++
template <typename T>
Matrix2d<T> adjugate(const Matrix2d<T> &matIn)
```

<p>Calculates adjugate of the input matrix.</p><br>

```C++
template <typename T>
Matrix2d<T> median(const Matrix2d<T> &matIn, const int direction) noexcept
```

<p>Calculates median of the input matrix in given direction. Direction 0 calculates median of the whole matrix. Direction 1 calculates the median row-wise (for every column). Direction 2 calculates the median column-wise (for every row).</p><br>

```C++
template <typename T>
Matrix2d<T> movmedian(const Matrix2d<T> &matIn, const int direction) noexcept
```

<p>Calculates moving median of the input matrix in given direction. Direction 0 calculates moving median of the whole matrix by sliding over the std::vector containing the data. Direction 1 calculates the moving median row-wise (for every column). Direction 2 calculates the moving median column-wise (for every row).</p><br>

```C++
template <typename T>
Matrix2d<T> mean(const Matrix2d<T> &matIn, const int direction) noexcept
```

<p>Calculates mean of the input matrix in given direction. Direction 0 calculates mean of the whole matrix. Direction 1 calculates the mean row-wise (for every column). Direction 2 calculates the mean column-wise (for every row).</p><br>

```C++
template <typename T>
Matrix2d<T> movmean(const Matrix2d<T> &matIn, const int direction) noexcept
```

<p>Calculates moving mean of the input matrix in given direction. Direction 0 calculates moving mean of the whole matrix by sliding over the std::vector containing the data. Direction 1 calculates the moving mean row-wise (for every column). Direction 2 calculates the moving mean column-wise (for every row).</p><br>

```C++
template <typename T>
Matrix2d<T> glm(const Matrix2d<T> &X, const Matrix2d<T> &Y) noexcept {
	if (X.getRows() != Y.getRows())
		return Matrix2d<T>();
	return (!(~X*X))*(~X)*Y;
}
```

<p>Calculates generalized linear model by modeling data matrix X to data vector Y. Matrix X should have all the data in column vectors. This means that the amount of columns in X matches the amount of indepenedent variables and the amount of rows in X matches the amount of data points in the data set. Target vector Y should be a column vector.</p><br>

```C++
template <typename T>
Matrix2d<T> operator+(Matrix2d<T> lhs, const T &rhs)
template <typename T>
Matrix2d<T> operator+(const T &lhs, Matrix2d<T> rhs)
template <typename T>
Matrix2d<T> operator-(Matrix2d<T> lhs, const T &rhs)
template <typename T>
Matrix2d<T> operator-(const T &lhs, Matrix2d<T> rhs)
template <typename T>
Matrix2d<T> operator*(Matrix2d<T> lhs, const T &rhs)
template <typename T>
Matrix2d<T> operator*(const T &lhs, Matrix2d<T> rhs)
template <typename T>
Matrix2d<T> operator/(Matrix2d<T> lhs, const T &rhs)
template <typename T>
Matrix2d<T> operator/(const T &lhs, Matrix2d<T> rhs)
```

<p>The operators for simple element by element summing, subtracting, multiplying and division between scalars and matrices<p><br>