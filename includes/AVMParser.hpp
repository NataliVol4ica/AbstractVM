
#pragma once

#include "defines.hpp"
#include "OperandFactory.hpp"
#include <vector>
#include <regex>

class AVMParser
{
public:
	AVMParser();
	AVMParser(std::vector<std::string> lines);

private:
	std::vector<std::string> _lines;
	const std::regex _regEx = std::regex(
		"\\G\\s*("
			"((push|assert)\\s*("
				"((int8|int16|int32)\\(-?\\d+\\))|"
				"((float|double)\\(-?\\d+(.\\d+)?\\)))"
				")|"
			"pop|dump|add|sub|mul|div|mod|print|exit"
		")\\s*\\Z");
};