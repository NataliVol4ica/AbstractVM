
#include "Operand.hpp"
#include "avmFuncs.hpp"
#include "OperandFactory.hpp"

#include <cfloat>
#include <stdio.h> 
//todo: canonic form

int main(void)
{
	int a;
	new Operand<char>();
	cout << INT32_MAX << " " << FLT_MAX << " " << DBL_MAX << endl;
	cout << INT32_MIN << " " << FLT_MIN << " " << DBL_MIN << endl;
	cout << (INT32_MAX > DBL_MAX) << endl;
	cout << (INT32_MIN < -DBL_MAX) << endl;
	cin >> a;
	return 0;
}
