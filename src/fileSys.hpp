#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

namespace fileSys {
	template <typename T>
	bool readFile(std::vector<std::string> &dataVec, const T path, const char delim) {
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
					dataVec.emplace_back(subStr);
			}
		}
		inStream.close();
		return true;
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
