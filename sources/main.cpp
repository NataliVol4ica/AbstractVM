
#include "Operand.hpp"
#include "avmFuncs.hpp"
#include "OperandFactory.hpp"

#include <cfloat>
#include <stdio.h> 
//todo: canonic form
//todo: log flag
int main(void)
{	
	try
	{
		OperandFactory of = OperandFactory();
		const IOperand *a = of.createOperand(Int8, "gdgdf");
		const IOperand *b = of.createOperand(Int8, "1");
		const IOperand *c =  *a + *b;
		cout << c->toString() << endl;
	}
	catch(exception &e)
	{		
		cout <<"Error: "<< e.what() << endl;
	}
	return 0;
}
