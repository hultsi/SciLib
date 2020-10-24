#include <iostream>
#include <string>
#include <chrono>

#include "scilib.h"
#include "fileSys.h"

using namespace std::chrono;

void testFun() {
	fileSys::file<double> file;
	fileSys::readFile(file, "./data/data.txt", '\t');

	scilib::Matrix2d<double> mat1(2,2);
	scilib::Matrix2d<double> mat2(file);
	scilib::Matrix2d<double> mat3 = mat2*mat2;

	// auto start = high_resolution_clock::now();
	// for (int i = 0; i < 10000; ++i)
	// 	scilib::determinant2(mat2);
	// auto stop = high_resolution_clock::now();
	// auto duration = duration_cast<microseconds>(stop - start); 
	// std::cout << duration.count() << "\n";

	std::cout << "finished\n";
}

int main() {
	testFun();

	return 0;
}