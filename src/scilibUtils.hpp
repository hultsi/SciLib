#pragma once

#include <string>

namespace scilibUtils {
	bool isDigit(std::string &str) {
		for (const char &c : str) {
			if ( !(c >= 48 && c <= 57) )
				return false;
		}
		return true;
	}

	bool isDigit(char &c) {
		return (c >= 48 && c <= 57);
	}

	bool isBasicOperator(std::string &str) {
		if (str.size() > 1)
			return false;
		return ( str == "+" || str == "-" || str == "*" || str == "/" );
	}

	bool isBasicOperator(char &c) {
		return ( c == '+' || c == '-' || c == '*' || c == '/' );
	}
}