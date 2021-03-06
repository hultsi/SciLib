#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

namespace fileSys {
	template <typename T>
	struct file {
		std::vector<T> data;
		int rows = 0;
		int columns = 0;
	};

	template <typename T>
	bool readFile(file<std::string> &dataStruct, const T path, const char delim) {
		std::string line;
		std::ifstream inStream(path);
		if (!inStream) {
			std::cerr << "Can't open the file : " << path << "\n";
			return false;
		}
		while (std::getline(inStream, line, '\n')) {
			if (line.size() > 0) {
				std::istringstream lineStream(line);
				std::string subStr;
				while (std::getline(lineStream, subStr, delim))
					dataStruct.data.emplace_back(subStr);
			}
			++dataStruct.rows;
		}
		dataStruct.columns = dataStruct.data.size()/dataStruct.rows;
		inStream.close();
		return true;
	}

	template <typename T>
	bool readFile(file<int> &dataStruct, const T path, const char delim) {
		std::string line;
		std::ifstream inStream(path);
		if (!inStream) {
			std::cerr << "Can't open the file : " << path << "\n";
			return false;
		}
		while (std::getline(inStream, line, '\n')) {
			if (line.size() > 0) {
				std::istringstream lineStream(line);
				std::string subStr;
				while (std::getline(lineStream, subStr, delim))
					dataStruct.data.emplace_back(std::stoi(subStr));
			}
			++dataStruct.rows;
		}
		dataStruct.columns = dataStruct.data.size()/dataStruct.rows;
		inStream.close();
		return true;
	};

	template <typename T>
	bool readFile(file<float> &dataStruct, const T path, const char delim) {
		std::string line;
		std::ifstream inStream(path);
		if (!inStream) {
			std::cerr << "Can't open the file : " << path << "\n";
			return false;
		}
		while (std::getline(inStream, line, '\n')) {
			if (line.size() > 0) {
				std::istringstream lineStream(line);
				std::string subStr;
				while (std::getline(lineStream, subStr, delim))
					dataStruct.data.emplace_back(std::stof(subStr));
			}
			++dataStruct.rows;
		}
		dataStruct.columns = dataStruct.data.size()/dataStruct.rows;
		inStream.close();
		return true;
	};

	template <typename T>
	bool readFile(file<double> &dataStruct, const T path, const char delim) {
		std::string line;
		std::ifstream inStream(path);
		if (!inStream) {
			std::cerr << "Can't open the file : " << path << "\n";
			return false;
		}
		while (std::getline(inStream, line, '\n')) {
			if (line.size() > 0) {
				std::istringstream lineStream(line);
				std::string subStr;
				while (std::getline(lineStream, subStr, delim))
					dataStruct.data.emplace_back(std::stod(subStr));
			}
			++dataStruct.rows;
		}
		dataStruct.columns = dataStruct.data.size()/dataStruct.rows;
		inStream.close();
		return true;
	};
}
