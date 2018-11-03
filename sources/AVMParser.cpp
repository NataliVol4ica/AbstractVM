#include "AVMParser.hpp"

/* ======== CANONICAL ======== */

AVMParser::AVMParser() {}

void AVMParser::Parse(std::vector<std::string> program)
{
	int errors = 0;
	for (size_t i = 0; i < program.size(); i++)
	{
		std::vector<std::string> stringTokens = Tokenize(program[i], i, errors);
		if (errors == 0)
		{
			std::vector<LexemToken> lTokens = RecognizeLexems(stringTokens);
			//check errors try catch
			//recognize lexems (struct string + enum)
			//compile
		}
	}
	cout << "Errors in total: " << errors << endl;
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
			lTokens.push_back(LexemToken(tokens[i], lexemMap.at(tokens[i])));
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

