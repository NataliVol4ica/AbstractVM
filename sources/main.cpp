
#include "Operand.hpp"
#include "avmFuncs.hpp"
#include "OperandFactory.hpp"

#include <cfloat>
#include <stdio.h> 
//todo: canonic form
//todo: log flag
int main(void)
{
	/*new Operand<char>();
	cout << INT32_MAX << " " << FLT_MAX << " " << DBL_MAX << endl;
	cout << INT32_MIN << " " << FLT_MIN << " " << DBL_MIN << endl;
	cout << (INT32_MAX > DBL_MAX) << endl;
	cout << (INT32_MIN < -DBL_MAX) << endl;*/
	try
	{
		OperandFactory of = OperandFactory();
		const IOperand *a = of.createOperand(Int8, "127");
		const IOperand *b = of.createOperand(Int8, "43");
		const IOperand *c =  *a + *b;
		cout << c->toString() << endl;
	}
	catch(exception &e)
	{		
		cout <<"Error: "<< e.what() << endl;
	}
	return 0;
}
