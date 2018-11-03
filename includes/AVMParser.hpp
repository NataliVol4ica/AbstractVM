
#pragma once

#include "defines.hpp"
#include "OperandFactory.hpp"
#include <vector>
#include <regex>

class AVMParser
{
public:
	AVMParser();
	void Parse(std::vector<std::string> program);

private:
	std::vector<std::string> Tokenize(std::string program, size_t line);
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
		"\\s*("
		"(;.*)|"
		"push|assert|pop|dump|add|sub|mul|div|mod|print|exit|"
		"int8|int16|int32|float|double|"
		"\\(|\\)|"
		"[+-]?\\d+(.\\d+)?"
		")\\s*");
};

enum eLexemType
{
	singleOp,
	paramOp,
	paramType,
	oBr,
	cBr,
	intNum,
	fracNum,
	newLine,
	comment,
	garbage
};