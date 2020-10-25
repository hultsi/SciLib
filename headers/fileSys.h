#pragma once

#include <vector>
#include <string>
#include <chrono>

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

#include "fileSys.hpp"