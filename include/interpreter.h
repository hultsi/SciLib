#pragma once

#include <string>
#include <vector>

/**
 * Used for interpreting scilib commands
 **/
namespace interpreter {
	std::vector<std::string> tokenize(std::string cmd);
	bool verifyTokens(std::vector<std::string> tokens);
}

#include "interpreter.hpp"
