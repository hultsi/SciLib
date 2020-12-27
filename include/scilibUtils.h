#pragma once

#include <string>

/**
 * Used for interpreting scilib commands
 **/
namespace scilibUtils {
	bool isDigit(std::string &str);
	bool isDigit(char &c);
	bool isBasicOperator(std::string &str);
	bool isBasicOperator(char &c);
}

#include "scilibUtils.hpp"