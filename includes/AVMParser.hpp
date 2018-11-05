
#pragma once

#include "defines.hpp"
#include "OperandFactory.hpp"
#include "eOperandType.hpp"
#include "eLexemType.hpp"
#include "LexemToken.hpp"
#include <vector>
#include <regex>
#include <map>
#include <stack>

//todo: canonical

class AVMParser
{
public:
	AVMParser();
	AVMParser(const AVMParser &ref);
	AVMParser& operator=(const AVMParser &ref);
	~AVMParser();
	void Parse(std::vector<std::string> program);
	class AVMParseException : public exception
	{
	public:
		AVMParseException();
		AVMParseException(std::string msg);
		AVMParseException(AVMParseException const &ref);
		AVMParseException &operator=(AVMParseException const &ref);
		~AVMParseException() throw();
		virtual const char* what() const throw();
	private:
		std::string		_msg;
	};

private:
	std::vector<std::string> Tokenize(std::string program, size_t line, int &errors);
	std::vector<LexemToken> RecognizeLexems(std::vector<std::string> tokens);
	void SyntaxAnal(std::vector<LexemToken> lTokens, size_t line, int &errors);
	void Run(std::vector<LexemToken> tokens, size_t line);

	eOperandType RecognizeType(std::string str);
	
	/* ops */
	void push(eOperandType type, std::string value, size_t line);
	void assert(eOperandType type, std::string value, size_t line);

	void pop(size_t line);
	void dump(size_t line);
	void add(size_t line);
	void sub(size_t line);
	void mul(size_t line);
	void div(size_t line);
	void mod(size_t line);
	void print(size_t line);
	void exit(size_t line);
	void size(size_t line); //prints current stack size
	void clean(size_t line); //cleans the whole stack

	/* vars */

	bool _toExit;

	typedef void(AVMParser::*paramFunc)(eOperandType, std::string, size_t);
	typedef void(AVMParser::*singleFunc)(size_t);

	std::vector<const IOperand*> opStack;
	static const OperandFactory _of;

	static const std::regex _lexemRegEx;
	static const std::map<std::string, eLexemType> _lexemMap;
	static const std::map<std::string, paramFunc > _paramCmdMap;
	static const std::map<std::string, singleFunc> _singleCmdMap;
};
