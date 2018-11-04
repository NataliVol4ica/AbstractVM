
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
	void SyntaxAnal(std::vector<LexemToken> lTokens, size_t line, int &errors);
	
	static const std::regex _lexemRegEx;
	static const std::map<std::string, eLexemType> _lexemMap;
};
