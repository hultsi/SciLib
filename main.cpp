#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

#include "scilib.h"
#include "fileSys.h"

using namespace std::chrono;

void timer(std::function<void()> fun, std::string timerName = "something") {
	const int loops = 10000;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < loops; ++i)
		fun();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
	std::cout << "Ran " << loops << " loops of " << timerName <<
			" -- Result: " << duration.count() << " milliseconds\n";
}

void testFun() {
	fileSys::file<int> file1;
	fileSys::readFile(file1, "./data/data.txt", '\t');
	fileSys::file<float> file2;
	fileSys::readFile(file2, "./data/data.txt", '\t');
	fileSys::file<double> file3;
	fileSys::readFile(file3, "./data/data.txt", '\t');

	scilib::Matrix2d<double> mat1(file3);
	scilib::Matrix2d<double> mat2(file3);
	
	//timer([&mat1,&mat2](){ mat1*mat2; }, "timer 1");
	scilib::Matrix2d<double> mat3 = scilib::movmedian(mat1,3,1);
	mat1.print();
	mat3.print();
}

int main() {
	testFun();

	return 0;
}