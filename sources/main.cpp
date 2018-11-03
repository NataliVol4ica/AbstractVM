#include "defines.hpp"
#include "AVMParser.hpp"
#include <stdio.h>
#include <vector>

//todo: canonic form
//todo: log flag
//todo: more funcs

int main(void)
{	
	try
	{
		std::vector<std::string> lines(2);
		lines[0] = "push int32(42);";
		lines[1] = "push int8(42)";

	/*	OperandFactory of = OperandFactory();
		const IOperand *a = of.createOperand(Int8, "gdgdf");
		const IOperand *b = of.createOperand(Int8, "1");
		const IOperand *c =  *a + *b;
		cout << c->toString() << endl;
	*/
	}
	catch(exception &e)
	{		
		cout <<"Error: "<< e.what() << endl;
	}
	//getchar();
	return 0;
}
/*std::ifstream t("file.txt");
std::stringstream buffer;
buffer << t.rdbuf();

Now the contents of "file.txt" are available in a string as buffer.str().*/
//read from std while cin does not match ";;.*"
