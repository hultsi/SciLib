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
	
	std::string cmd("1+12-213*23/292929-2asd123");
	std::vector<std::string> tokens = interpreter::tokenize(cmd);
	const bool allGood = interpreter::verifyTokens(tokens);
	if (allGood)
		std::cout << "All is well\n";
	else
		std::cout << interpreter::tokenError << "\n";

	return 0;
}