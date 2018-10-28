
#include "eOperandType.hpp"
#include "Operand.hpp"
#include "avmFuncs.hpp"
#include "defines.hpp"

IOperand const * createOperand(eOperandType type, string const & value ) const
{
	if (type == Int8)
		return (IOperand)(new Operand<char>(static_cast<char>(stoi(value))));
	if (type == Int16)
		return (IOperand)(new Operand<char>(static_cast<short>(stoi(value))));
	if (type == Int32)
		return (IOperand)(new Operand<char>(stoi(value)));
	if (type == Float)
		return (IOperand)(new Operand<char>(stof(value)));
	if (type == Double)
		return (IOperand)(new Operand<char>(stod(value)));
	//throw exception?
}