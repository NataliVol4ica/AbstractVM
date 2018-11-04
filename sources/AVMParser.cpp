#include "AVMParser.hpp"

/* ======== CANONICAL ======== */

AVMParser::AVMParser() :_toExit(false) {}

AVMParser::~AVMParser()
{
	const IOperand *top;
	while (opStack.size() > 0)
	{
		top = opStack.back();
		delete(top);
		opStack.pop_back();
	}
}
/* ==== PARSING ==== */

void AVMParser::Parse(std::vector<std::string> program)
{
	int errors = 0;
	std::vector<std::vector<std::string>> stringTokens;
	std::vector<std::vector<LexemToken>> lTokens;
	for (size_t i = 0; i < program.size(); i++)
		stringTokens.push_back(Tokenize(program[i], i + 1, errors));
	if (errors != 0)		
		throw AVMParseException("Shutting down: Program has " + std::to_string(errors) + " lexical errors");
	for (size_t i = 0; i < program.size(); i++)
	{
		lTokens.push_back(RecognizeLexems(stringTokens[i]));
		SyntaxAnal(lTokens[i], i + 1, errors);
	}
	if (errors != 0)		
		throw AVMParseException("Shutting down: Program has " + std::to_string(errors) + " syntax errors");
	for (size_t i = 0; i < program.size(); i++)
	{
		Run(lTokens[i], i + 1);
		if (_toExit)
			break;
	}
	if (!_toExit)
	{
		cout <<"throwing"<<endl;
		throw AVMParseException("Error: Program is missing exit");
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
	{
		eOperandType type = RecognizeType(tokens[1].str);
		paramFunc pf = _paramCmdMap.at(tokens[0].str);
		(this->*pf)(type, tokens[3].str, line);
	}
	else
		(this->*_singleCmdMap.at(tokens[0].str))(line);
}
eOperandType AVMParser::RecognizeType(std::string str)
{
	//todo: replace with map
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
		opStack.push_back(_of.createOperand(type, value));
	}
	catch (exception &e)
	{
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
}
void AVMParser::assert(eOperandType type, std::string value, size_t line)
{
	const IOperand *top = opStack.back();
	if (top->getType() != type || top->toString() != value)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": assert failed");
}

void AVMParser::pop(size_t line)
{
	if (opStack.size() == 0)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Pop on empty stack");
	const IOperand *top = opStack.back();
	delete(top);
	opStack.pop_back();
}
void AVMParser::dump(size_t line)
{
	for (size_t i = 0; i < opStack.size(); i++)
		cout <<opStack[i]->toString()<<endl;
	(void)line;
	//todo: think of exception?
}
void AVMParser::add(size_t line)
{
	if (opStack.size() < 2)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Less than 2 operands in the stack");
	const IOperand *a, *b;
	b = opStack.back();
	opStack.pop_back();
	a = opStack.back();
	opStack.pop_back();
	try
	{	
		opStack.push_back(*a + *b);
	}	
	catch (exception &e)
	{
		delete(a);
		delete(b);
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
	delete(a);
	delete(b);
}
void AVMParser::sub(size_t line)
{
	if (opStack.size() < 2)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Less than 2 operands in the stack");
	const IOperand *a, *b;
	b = opStack.back();
	opStack.pop_back();
	a = opStack.back();
	opStack.pop_back();
	try
	{	
		opStack.push_back(*a - *b);
	}	
	catch (exception &e)
	{
		delete(a);
		delete(b);
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
	delete(a);
	delete(b);
}
void AVMParser::mul(size_t line)
{
	if (opStack.size() < 2)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Less than 2 operands in the stack");
	const IOperand *a, *b;
	b = opStack.back();
	opStack.pop_back();
	a = opStack.back();
	opStack.pop_back();
	try
	{	
		opStack.push_back(*a * *b);
	}	
	catch (exception &e)
	{
		delete(a);
		delete(b);
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
	delete(a);
	delete(b);
}
void AVMParser::div(size_t line)
{
	if (opStack.size() < 2)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Less than 2 operands in the stack");
	const IOperand *a, *b;
	b = opStack.back();
	opStack.pop_back();
	a = opStack.back();
	opStack.pop_back();
	try
	{	
		opStack.push_back(*a / *b);
	}	
	catch (exception &e)
	{
		delete(a);
		delete(b);
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
	delete(a);
	delete(b);
}
void AVMParser::mod(size_t line)
{
	if (opStack.size() < 2)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Less than 2 operands in the stack");
	const IOperand *a, *b;
	b = opStack.back();
	opStack.pop_back();
	a = opStack.back();
	opStack.pop_back();
	try
	{	
		opStack.push_back(*a % *b);
	}	
	catch (exception &e)
	{
		delete(a);
		delete(b);
		throw AVMParseException("Error: Line " + std::to_string(line) + ": " + e.what());
	}
	delete(a);
	delete(b);
}
void AVMParser::print(size_t line)
{
	if (opStack.size() == 0)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": Print on empty stack");
	const IOperand *top = opStack.back();
	if (top->getType() != Int8)
		throw AVMParseException("Error: Line " + std::to_string(line) + ": The top element is not Int8");
	cout<<(char)stoi(top->toString())<<endl;
}
void AVMParser::exit(size_t line)
{
	_toExit = true;
	(void)line;
}
void AVMParser::size(size_t line)
{
	cout<<opStack.size()<<endl;
	(void)line;
}
void AVMParser::clean(size_t line)
{
	const IOperand *top;
	while (opStack.size() > 0)
	{
		top = opStack.back();
		delete(top);
		opStack.pop_back();
	}
	(void)line;
}

/* ==== VARIABLES ==== */

const OperandFactory AVMParser::_of = OperandFactory();
const std::regex AVMParser::_lexemRegEx = std::regex(
		"\\s*("
		"(;.*)|"
		"push|assert|pop|dump|add|sub|mul|div|mod|print|exit|size|clean|"
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
	{ "size", singleOp },
	{ "clean", singleOp },
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
	{"pop", &AVMParser::pop},
	{"dump", &AVMParser::dump},
	{"add", &AVMParser::add},
	{"sub", &AVMParser::sub},
	{"mul", &AVMParser::mul},
	{"div", &AVMParser::div},
	{"mod", &AVMParser::mod},
	{"print", &AVMParser::print},
	{"exit", &AVMParser::exit},
	{"size", &AVMParser::size},
	{"clean", &AVMParser::clean}
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
