# **SciLib**

Library for matrix manipulation, modeling etc. At the moment the library includes 2 namespaces, fileSys and scilib.

## Includes
- ## fileSys.h
	- Used for reading and loading data from from/to hard drive
- ## scilib.h
	- Contains the Matrix2d class and functions for manipulating it

# Documentation

## <span style="position: relative; display: inline-block; left: 50%; transform: translateX(-50%); font-size: 25px">**<fileSys.h>**</span>
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

## <span style="position: relative; display: inline-block; left: 50%; transform: translateX(-50%); font-size: 25px">**<scilib.h>**</span>
## **Contains**
- <span style="font-size: 18px">class Matrix2d< T ></span>
- <span style="font-size: 18px">T determinant< T >(const Matrix2d< T > &)</span>
- ...

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px">class matrix::Matrix2d< T ></span>

```C++
template <typename T>
class Matrix2d;
```

The matrix class of the library. Details about the class itself later on.

## <span style="letter-spacing: 1px; border-bottom: 1px solid rgba(255,255,255,.5); padding: 2px">T matrix::determinant< T >()</span>

```C++
template <typename T>
T determinant(const Matrix2d<T> &matIn);
```