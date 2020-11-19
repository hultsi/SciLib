#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace interpreter {
	constexpr char PLUS = '+';
	constexpr char MINUS = '-';
	constexpr char PRODUCT = '*';
	constexpr char DIVISION = '/';

	std::vector<std::string> tokenize(std::string cmd) {
		std::vector<std::string> tokens;

		tokens.emplace_back(cmd.substr(0,1));
		cmd = cmd.substr(1);

		bool prevWasNum = true;
		for (const char &c : cmd) {
			if (c == PLUS) {
				tokens.emplace_back(std::string(1,c));
				prevWasNum = false;
			} else if (c == MINUS) {
				tokens.emplace_back(std::string(1,c));
				prevWasNum = false;
			} else if (c == PRODUCT) {
				tokens.emplace_back(std::string(1,c));
				prevWasNum = false;
			} else if (c == DIVISION) {
				tokens.emplace_back(std::string(1,c));
				prevWasNum = false;
			} else if (c >= 48 && c <= 57) {
				if (prevWasNum)
					tokens.back() += c;
				else
					tokens.emplace_back(std::string(1,c));

				prevWasNum = true;
			}
		}
		return tokens;
	}
}