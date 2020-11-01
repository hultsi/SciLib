#include <iostream>
#include <string>
#include <chrono>

#include "scilib.h"
#include "fileSys.h"

using namespace std::chrono;

void testFun() {
	fileSys::file<int> file1;
	fileSys::readFile(file1, "./data/data.txt", '\t');
	fileSys::file<float> file2;
	fileSys::readFile(file2, "./data/data.txt", '\t');
	fileSys::file<double> file3;
	fileSys::readFile(file3, "./data/data.txt", '\t');

	scilib::Matrix2d<double> mat1(file3);
	scilib::Matrix2d<double> mat2(file3);
	mat1*mat2;
	// mat1(0,0) = 1;
	// mat1(1,0) = 2;
	// mat1(2,0) = 3;
	// mat1(3,0) = 4;
	// scilib::Matrix2d<double> mat2(file);
	// //scilib::Matrix2d<double> mat3 = mat2*mat2;
	
	// // scilib::mean(mat2,1).print();
	// // scilib::mean(mat2,2).print();
	// (mat2*scilib::glm(mat2,mat1)).print();
	// auto start = high_resolution_clock::now();
	// for (int i = 0; i < 10000; ++i)
	// 	fileSys::readFile(file, "./data/data.txt", '\t');
	// auto stop = high_resolution_clock::now();
	// auto duration = duration_cast<microseconds>(stop - start); 
	// std::cout << duration.count() << "\n";
}

int main() {
	testFun();

	return 0;
}