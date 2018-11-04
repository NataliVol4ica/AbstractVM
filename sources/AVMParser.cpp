#include "AVMParser.hpp"

/* ======== CANONICAL ======== */

AVMParser::AVMParser() {}

/* ==== PARSING ==== */

void AVMParser::Parse(std::vector<std::string> program)
{
	int errors = 0;
	std::vector<std::string> stringTokens [program.size()];
	std::vector<LexemToken> lTokens [program.size()];
	for (size_t i = 0; i < program.size(); i++)
		stringTokens[i] = Tokenize(program[i], i + 1, errors);
	//todo: create exception
	cout << "Lexical errors in total: " << errors << endl;
	if (errors != 0)
		return;
	for (size_t i = 0; i < program.size(); i++)
	{
		lTokens[i] = RecognizeLexems(stringTokens[i]);
		SyntaxAnal(lTokens[i], i + 1, errors);
	}
	//todo: create exception
	cout << "Syntax errors in total: " << errors << endl;
	if (errors != 0)
		return;
	try
	{
		for (size_t i = 0; i < program.size(); i++)
			Run(lTokens[i], i + 1);
	}
	catch (exception &e)
	{
		cout <<e.what()<<endl;
	}
}
std::vector<std::string> AVMParser::Tokenize(std::string program, size_t line, int &errors)
{
	std::vector<std::string> tokens;
	std::smatch sm;
	std::string str;
	while (regex_search(program, sm, _lexemRegEx))
	{
		if (sm.prefix().length() != 0)
		{
			errors++;
			cout << "Line " << line << ": unknow lexem \"" << sm.prefix() << "\"" << endl;
		}
		str = sm.str();
		str.erase(0, str.find_first_not_of("\t\n\v\f\r "));
		str.erase(str.find_last_not_of("\t\n\v\f\r ") + 1);
		tokens.push_back(str);
		program = sm.suffix();
	}
	if (program.length() > 0)
	{
		errors++;
		cout << "Line " << line << ": unknow lexem \"" << program << "\"" << endl;
	}
	return tokens;
}
std::vector<LexemToken> AVMParser::RecognizeLexems(std::vector<std::string> tokens)
{
	std::vector<LexemToken> lTokens;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		try
		{
			lTokens.push_back(LexemToken(tokens[i], _lexemMap.at(tokens[i])));
		}
		catch (exception)
		{
			//cout << "\"" << tokens[i] << "\"" << endl;
			if (tokens[i][0] == ';')
				lTokens.push_back(LexemToken(tokens[i], comment));
			else if (tokens[i].find(".") != std::string::npos)
				lTokens.push_back(LexemToken(tokens[i], fracNum));
			else
				lTokens.push_back(LexemToken(tokens[i], intNum));
		}
	}
	return lTokens;
}
void AVMParser::SyntaxAnal(std::vector<LexemToken> lTokens, size_t line, int &errors)
{
	if (lTokens.size() == 0)
		return;
	switch(lTokens[0].type)
	{
		case comment:
			return;
		case singleOp:
		{
			if (lTokens.size() == 1 || lTokens[1].type == comment)
				return;
			errors++;
			cout << "Line "<<line<<": Syntax error: "<<lTokens[0].str<<" has too many arguments" <<endl;
			return;
		}
		case paramOp:
		{
			if (lTokens.size() < 5)
			{
				errors++;
				cout << "Line "<<line<<": Syntax error: command does not fit format \"cmd type(value)\"" <<endl;
				return;
			}			
			if (lTokens[1].type != paramIntType && lTokens[1].type != paramFracType)
			{
				errors++;
				cout << "Line "<<line<<": Syntax error: "<<lTokens[1].str<<" is not a value type" <<endl;
				return;
			}
			if (lTokens[2].type != oBr)
			{
				errors++;
				cout << "Line "<<line<<": Syntax error: "<<lTokens[2].str<<" is not an opening bracket" <<endl;
				return;
			}			
			if ((lTokens[3].type != intNum && lTokens[3].type != fracNum) || 
				(lTokens[1].type == paramIntType && lTokens[3].type == fracNum))
			{
				errors++;
				cout << "Line "<<line<<": Syntax error: "<<lTokens[1].str<<" is missing proper value (having "<<lTokens[3].str<<")" <<endl;
				return;
			}
			if (lTokens[4].type != cBr)
			{
				errors++;
				cout << "Line "<<line<<": Syntax error: "<<lTokens[4].str<<" is not a closing bracket" <<endl;
				return;
			}		
			if (lTokens.size() == 5 || lTokens[5].type == comment)
				return;
			errors++;
			cout << "Line "<<line<<": Syntax error: "<<lTokens[0].str<<" has too many arguments" <<endl;
			return;
		}
		default:
		{			
			errors++;
			cout << "Line "<<line<<": Syntax error: line has to start with command" <<endl;
			//todo: process string starting of something not being a comment
		}
	}
}
void AVMParser::Run(std::vector<LexemToken> tokens, size_t line)
{
	//100% valid
	if (tokens.size() == 0 || tokens[0].type == comment)
		return;
	if (tokens[0].type == paramOp)
		(this->*_paramCmdMap.at(tokens[0].str))(RecognizeType(tokens[1].str), tokens[3].str, line);
	else		
		(this->*_singleCmdMap.at(tokens[0].str))(line);
}
eOperandType AVMParser::RecognizeType(std::string str)
{
	if (str == "int8")
		return Int8;
	if (str == "int16")
		return Int16;
	if (str == "int32")
		return Int32;
	if (str == "float")
		return Float;
	if (str == "double")
		return Double;
	return None;
}

/* ==== COMMANDS ==== */

void AVMParser::push(eOperandType type, std::string value, size_t line)
{
	try
	{
		opStack.push(_of.createOperand(type, value));
	}
	catch (exception &e)
	{
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
}
void AVMParser::assert(eOperandType type, std::string value, size_t line)
{
	(void)type;
	(void)value;
	(void)line;
}

void AVMParser::pop(size_t line)
{
	try
	{
		opStack.pop();
	}
	catch (exception &e)
	{
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Pop on empty stack");
	}
}

/* ==== VARIABLES ==== */

const OperandFactory AVMParser::_of = OperandFactory();
const std::regex AVMParser::_lexemRegEx = std::regex(
		"\\s*("
		"(;.*)|"
		"push|assert|pop|dump|add|sub|mul|div|mod|print|exit|"
		"int8|int16|int32|float|double|"
		"\\(|\\)|"
		"[+-]?\\d+(.\\d+)?"
		")\\s*");
const std::map<std::string, eLexemType> AVMParser::_lexemMap = {
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
	{ "int8", paramIntType },
	{ "int16", paramIntType },
	{ "int32", paramIntType },
	{ "Float", paramFracType },
	{ "Double", paramFracType },
	{"(", oBr},
	{")", cBr}
	};
const std::map<std::string, AVMParser::paramFunc> AVMParser::_paramCmdMap = {
	{"push", &AVMParser::push},
	{"assert", &AVMParser::assert}
};
const std::map<std::string, AVMParser::singleFunc> AVMParser::_singleCmdMap = {
	{"pop", &AVMParser::pop}
};

/* ==== EXCEPTIONS ==== */

AVMParser::AVMParseException::AVMParseException(){}
AVMParser::AVMParseException::AVMParseException(std::string msg):_msg(msg) {}
AVMParser::AVMParseException::AVMParseException(AVMParseException const &ref){*this = ref;}
AVMParser::AVMParseException &AVMParser::AVMParseException::operator=(AVMParseException const &ref)
{
	exception::operator=(ref);
	return *this;
}
AVMParser::AVMParseException::~AVMParseException() throw() {}
const char* AVMParser::AVMParseException::what() const throw()
{
	return _msg.c_str();
}
