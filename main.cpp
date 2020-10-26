#include <iostream>
#include <string>
#include <chrono>

#include "scilib.h"
#include "fileSys.h"

using namespace std::chrono;

void testFun() {
	fileSys::file<double> file;
	fileSys::readFile(file, "./data/data.txt", '\t');

	scilib::Matrix2d<double> mat1(3,1);
	mat1(0,0) = 1;
	mat1(1,0) = 2;
	mat1(2,0) = 3;
	scilib::Matrix2d<double> mat2(file);
	//scilib::Matrix2d<double> mat3 = mat2*mat2;
	
	scilib::mean(mat2,1).print();
	scilib::mean(mat2,2).print();
	//scilib::glm(mat2,mat1).print();
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