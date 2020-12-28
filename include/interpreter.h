#pragma once

#include <string>
#include <vector>

/**
 * Used for interpreting scilib commands
 **/
namespace interpreter {
	struct Result {
		int solved = 0; // 0 == not solved, 1 == number output, 2 == string output
		int num = 0;
		std::string str = "";
	};

	std::vector<std::string> tokenize(std::string cmd);
	bool verifyTokens(std::vector<std::string> tokens);
	void setTokenError(int err, std::string token);

	double processArithmeticExpr(std::vector<std::string> tokens);
	void processTokenSum(std::vector<std::string> &tokens);
	void processTokenSubtraction(std::vector<std::string> &tokens);
	void processTokenDivision(std::vector<std::string> &tokens);
	void processTokenMultiplication(std::vector<std::string> &tokens);

	double sum(std::string lhs, std::string rhs);
	double subtract(std::string lhs, std::string rhs);
	double divide(std::string lhs, std::string rhs);
	double multiply(std::string lhs, std::string rhs);
}

#include "interpreter.hpp"
