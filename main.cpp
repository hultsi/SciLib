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
	
	mat2.popRow(2);
	mat2.popColumn(1);
	mat2.print();
	//scilib::determinant(mat2);
	// auto start2 = high_resolution_clock::now();
	// auto stop2 = high_resolution_clock::now();
	// auto duration2 = duration_cast<microseconds>(stop2 - start2); 
	// std::cout << duration2.count() << "\n";

	std::cout << "finished\n";
}

int main() {
	testFun();

	return 0;
}