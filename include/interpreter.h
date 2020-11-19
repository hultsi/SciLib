#pragma once

#include <string>
#include <vector>

/**
 * Used for interpreting scilib commands
 **/
namespace interpreter {
	std::vector<std::string> tokenize(std::string cmd);
}

#include "interpreter.hpp"
