
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
	//todo: check if needed
	const std::regex _validRegEx = std::regex(
		"\\A\\s*("
		"((push|assert)\\s*("
		"((int8|int16|int32)\\(-?\\d+\\))|"
		"((float|double)\\(-?\\d+(.\\d+)?\\)))"
		")|"
		"pop|dump|add|sub|mul|div|mod|print|exit"
		")\\s*\\Z");
	const std::regex _lexemRegEx = std::regex(
		"\\G\\s*("
		"(;.*(\\n|\\z))|"
		"push|assert|pop|dump|add|sub|mul|div|mod|print|exit|"
		"int8|int16|int32|float|double|"
		"\\(|\\)|"
		"[+-]?\\d+(.\\d+)?|"
		"\\n"
		")\\s*");
};
//enum singleOp paramOp paramType oBr cBr intNum fracNum newLine comment garbage