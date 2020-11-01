#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace fileSys {
	template <typename T>
	struct file;

	template <typename T, typename H, typename N>
	bool readFile(file<T> &dataStruct, const H path, const char delim = '\t');

	template <typename T>
	bool readFile(file<std::string> &dataStruct, const T path, const char delim = '\t');
	template <typename T>
	bool readFile(file<int> &dataStruct, const T path, const char delim = '\t');
	template <typename T>
	bool readFile(file<float> &dataStruct, const T path, const char delim = '\t');
	template <typename T>
	bool readFile(file<double> &dataStruct, const T path, const char delim = '\t');
}

#include "fileSys.hpp"