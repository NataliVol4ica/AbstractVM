#include "AVMParser.hpp"

/* ======== CANONICAL ======== */

AVMParser::AVMParser() {}

void AVMParser::Parse(std::vector<std::string> program)
{
	for (size_t i = 0; i < program.size(); i++)
	{
		std::vector<std::string> stringTokens = Tokenize(program[i], i);
		//recognize lexems (struct string + enum)
		//compile
	}
}

std::vector<std::string> AVMParser::Tokenize(std::string program, size_t line)
{
	//todo:prefix has to be of len 0
	std::smatch sm;
	while (regex_search(program, sm, _lexemRegEx))
	{
		if (sm.prefix().length() != 0)
			cout << "Line "<<line<<": unknow lexem \"" << sm.prefix() << "\"" << endl;
		cout << sm.str() << '\n';
		program = sm.suffix();
	}
	return std::vector<std::string>();
}

