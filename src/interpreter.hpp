#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "scilibUtils.h"

namespace interpreter {
	constexpr char PLUS = '+';
	constexpr char MINUS = '-';
	constexpr char PRODUCT = '*';
	constexpr char DIVISION = '/';
	constexpr char DOT = '.';
	constexpr char LEFT_BRACKET = '(';
	constexpr char RIGHT_BRACKET = ')';

	enum errors {
		ERR_INVALID_VARIABLE_NAME
	};
	const std::array<std::string,1> errorMessages = {
		"Invalid variable name"
	};
	std::string tokenError = "";

	std::vector<std::string> tokenize(std::string cmd) {
		std::vector<std::string> tokens;

		tokens.emplace_back(cmd.substr(0,1));
		cmd = cmd.substr(1);

		bool prevNotOperator = false;
		for (const char &c : cmd) {
			if (c == PLUS) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == MINUS) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == PRODUCT) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == DIVISION) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == LEFT_BRACKET) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == RIGHT_BRACKET) {
				tokens.emplace_back(std::string(1,c));
				prevNotOperator = false;
			} else if (c == DOT || (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
				if (prevNotOperator)
					tokens.back() += c;
				else
					tokens.emplace_back(std::string(1,c));
				prevNotOperator = true;
			}
		}
		return tokens;
	}

	bool verifyTokens(std::vector<std::string> tokens) {
		// Does the command start or end with operator?
		if ( scilibUtils::isBasicOperator(tokens.at(0)) ) {
			return false;
		} else if ( scilibUtils::isBasicOperator(tokens.at(tokens.size()-1))) {
			return false;
		}
		
		int openBrackets = 0;
		bool prevWasOperator = false;
		for (const std::string &token : tokens) {
			if (token == "+") {
				if (prevWasOperator) {
					return false;
				}

				prevWasOperator = true;
			} else if (token == "-") {
				if (prevWasOperator) {
					return false;
				}

				prevWasOperator = true;
			} else if (token == "*") {
				if (prevWasOperator) {
					return false;
				}

				prevWasOperator = true;
			} else if (token == "/") {
				if (prevWasOperator) {
					return false;
				}

				prevWasOperator = true;
			} else if (token == "(") {
				++openBrackets;
			} else if (token == ")") {
				--openBrackets;
			} else {
				bool isVar = true;
				bool hasDot = false;
				// Is first char digit?
				if ( (char)token.at(0) >= 48 && (char)token.at(0) <= 57 ) {
					isVar = false;
				}
				if (!isVar) {
					// First char is digit, so every other char must also be digit
					for (const char &c : token) {
						if (!( (c >= 48 && c <= 57) || c == DOT) && !hasDot) {
							setTokenError(ERR_INVALID_VARIABLE_NAME, token);
							return false;
						}
						if (c == DOT) hasDot = true;
					}
				}
				prevWasOperator = false;
			}
		}
		if (openBrackets != 0)
			return false;
		return true;
	}

	void setTokenError(int err, std::string token) {
		std::string fullErr = "";
		fullErr += errorMessages.at(err);
		switch (err) {
			case ERR_INVALID_VARIABLE_NAME: {
				fullErr += " at ";
				fullErr += "\"";
				fullErr += token;
				fullErr += "\"";
				break;
			}
			default: {
				
				break;
			}
		}
		tokenError = fullErr;
	}

	double processArithmeticExpr(std::vector<std::string> tokens) {
		double result = 0;

		processTokenBrackets(tokens);
		processTokenDivision(tokens);
		processTokenMultiplication(tokens);
		processTokenSum(tokens);
		processTokenSubtraction(tokens);
	
		result = std::stod(tokens.at(0));

		return result;
	}

	void processTokenBrackets(std::vector<std::string> &tokens) {
		double tmpRes = 0;
		std::vector<std::string>::iterator closing = std::find(tokens.begin(), tokens.end(), ")");
		while (closing != tokens.end()) {
			std::vector<std::string>::iterator opening = closing;
			while (opening != tokens.begin()) {
				--opening;
				if (*opening == "(") break;
			}
			tmpRes = processArithmeticExpr(std::vector<std::string>(opening+1, closing));
			*opening = std::to_string(tmpRes);
			while (closing != tokens.end()-1) {
				++opening;
				++closing;
				*opening = *closing;
			}
			while (opening != tokens.end()-1)
				*++opening = "";

			closing = std::find(tokens.begin(), tokens.end(), ")");
		}
	}

	void processTokenSum(std::vector<std::string> &tokens) {
		bool solved = false;
		std::vector<std::string>::iterator it;
		while (!solved) {
			it = std::find(tokens.begin(), tokens.end(), "+");
			if (it != tokens.end()) {
				*(it-1) = std::to_string( sum( *(it-1), *(it+1) ) );
				while (it != tokens.end()-2) {
					*it = *(it+2);
					++it;
				}
				while (it != tokens.end())
					*it++ = "";
			} else {
				solved = true;
			}
		}
	}

	void processTokenSubtraction(std::vector<std::string> &tokens) {
		bool solved = false;
		std::vector<std::string>::iterator it;
		while (!solved) {
			it = std::find(tokens.begin(), tokens.end(), "-");
			if (it != tokens.end()) {
				*(it-1) = std::to_string( subtract( *(it-1), *(it+1) ) );
				while (it != tokens.end()-2) {
					*it = *(it+2);
					++it;
				}
				while (it != tokens.end())
					*it++ = "";
			} else {
				solved = true;
			}
		}
	}

	void processTokenDivision(std::vector<std::string> &tokens) {
		bool solved = false;
		std::vector<std::string>::iterator it;
		while (!solved) {
			it = std::find(tokens.begin(), tokens.end(), "/");
			if (it != tokens.end()) {
				*(it-1) = std::to_string( divide( *(it-1), *(it+1) ) );
				while (it != tokens.end()-2) {
					*it = *(it+2);
					++it;
				}
				while (it != tokens.end())
					*it++ = "";
			} else {
				solved = true;
			}
		}
	}

		void processTokenMultiplication(std::vector<std::string> &tokens) {
		bool solved = false;
		std::vector<std::string>::iterator it;
		while (!solved) {
			it = std::find(tokens.begin(), tokens.end(), "*");
			if (it != tokens.end()) {
				*(it-1) = std::to_string( multiply( *(it-1), *(it+1) ) );
				while (it != tokens.end()-2) {
					*it = *(it+2);
					++it;
				}
				while (it != tokens.end())
					*it++ = "";
			} else {
				solved = true;
			}
		}
	}

	double sum(std::string lhs, std::string rhs) {
		return std::stod(lhs) + std::stod(rhs);
	}

	double subtract(std::string lhs, std::string rhs) {
		return std::stod(lhs) - std::stod(rhs);
	}

	double divide(std::string lhs, std::string rhs) {
		return std::stod(lhs) / std::stod(rhs);
	}

	double multiply(std::string lhs, std::string rhs) {
		return std::stod(lhs) * std::stod(rhs);
	}
}