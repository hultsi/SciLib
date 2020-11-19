#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

#include "scilib.h"
#include "fileSys.h"
#include "interpreter.h"

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


int main() {
	
	std::string cmd("1+12-213*23/292929");
	std::vector<std::string> tokens = interpreter::tokenize(cmd);
	for (const std::string &str : tokens)
		std::cout << str << "\n";

	return 0;
}