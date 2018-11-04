
#pragma once

#include "defines.hpp"
#include "OperandFactory.hpp"
#include "eLexemType.hpp"
#include "LexemToken.hpp"
#include <vector>
#include <regex>
#include <map>

class AVMParser
{
public:
	AVMParser();
	void Parse(std::vector<std::string> program);

private:
	std::vector<std::string> Tokenize(std::string program, size_t line, int &errors);
	std::vector<LexemToken> RecognizeLexems(std::vector<std::string> tokens);
	//todo: check if needed
	/*const std::regex _validRegEx = std::regex(
		"\\A\\s*("
		"((push|assert)\\s*("
		"((int8|int16|int32)\\(-?\\d+\\))|"
		"((float|double)\\(-?\\d+(.\\d+)?\\)))"
		")|"
		"pop|dump|add|sub|mul|div|mod|print|exit"
		")\\s*\\Z");*/
	const std::regex _lexemRegEx = std::regex(
		"\\s*("
		"(;.*)|"
		"push|assert|pop|dump|add|sub|mul|div|mod|print|exit|"
		"int8|int16|int32|float|double|"
		"\\(|\\)|"
		"[+-]?\\d+(.\\d+)?"
		")\\s*");
	std::map<std::string, eLexemType> lexemMap = {
	{"push", paramOp},
	{"assert", paramOp},
	{ "pop", singleOp },
	{ "dump", singleOp },
	{ "add", singleOp },
	{ "sub", singleOp },
	{ "mul", singleOp },
	{ "div", singleOp },
	{ "mod", singleOp },
	{ "print", singleOp },
	{ "exit", singleOp },
	{ "int8", paramType },
	{ "int16", paramType },
	{ "int32", paramType },
	{ "Float", paramType },
	{ "Double", paramType },
	{"(", oBr},
	{")", cBr}
	};
	//try access map catch if coment or number
};
