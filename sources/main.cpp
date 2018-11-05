#include "defines.hpp"
#include "AVMParser.hpp"
#include <stdio.h>
#include <regex>
#include <vector>
#include <iomanip>
#include <fstream> 

//todo: more funcs
//todo: rm make tests

#define TOPRINTPROG 0

void printProg(std::string name, std::vector<std::string> program)
{
	int width = std::to_string(program.size() + 1).length();
	cout<<"================="<<endl;
	cout << "\t" <<name<<endl;
	for (size_t i = 0; i < program.size(); i++)
		cout << std::setfill('0') << std::setw(width) << i + 1 << " " << program[i] << endl;
	cout<<"================="<<endl;
}

void readFromStd(void)
{
	const std::regex eoReadRegEx("\\s*;;\\s*");
	std::vector<std::string> program;
	std::string rd;
	AVMParser p = AVMParser();
	while (true)
	{
		std::getline(cin, rd);
		if (std::regex_match(rd, eoReadRegEx))
			break;
		program.push_back(rd);
	}
	if (TOPRINTPROG)
		printProg("Program from std", program);
	try
	{
		p.Parse(program);
	}
	catch(exception &e)
	{		
		cout << e.what() << endl;
	}
	catch(exception *e)
	{		
		cout <<"Error: "<< e->what() << endl;
	}
}

void readFromFiles(const char *fileName)
{
	std::ifstream file(fileName);
	if(file.fail())
	{
		cout<<"================="<<endl;
		cout<<"Error: can't open file "<<fileName<<endl;
		cout<<"================="<<endl;
		file.close();
		return;
	}
	std::vector<std::string> program;
	std::string rd;
	AVMParser p = AVMParser();
	while (true)
	{
		std::getline(file, rd);
		program.push_back(rd);
		if (file.eof())
			break;
	}
	if (TOPRINTPROG)
		printProg("Program from " + std::string(fileName), program);	
	try
	{
		p.Parse(program);
	}
	catch(exception &e)
	{		
		cout << e.what() << endl;
	}
	catch(exception *e)
	{		
		cout <<"Error: "<< e->what() << endl;
	}
	file.close();
}

int main(int ac, char **av)
{	
	//cout.precision(17);
	if (ac == 1)
		readFromStd();
	else
		for (int i = 1; i < ac; i++)
			readFromFiles(av[i]);
	//system("leaks avm");
	return 0;
}
