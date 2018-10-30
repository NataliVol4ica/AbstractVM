
#include "IOperand.hpp"
#include "OperandFactory.hpp"

OperandFactory::func	OperandFactory::createFuncs[] =
{
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble
};

/* Canonical */
OperandFactory::OperandFactory() {}
OperandFactory::OperandFactory(const OperandFactory&) {}
OperandFactory & OperandFactory::operator=(const OperandFactory&) {}
OperandFactory::~OperandFactory() {}

/* Factory*/
IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	return createFuncs[type](value);
	/*if (type == Int8)
		return (new Operand<char>(static_cast<char>(stoi(value))));
	if (type == Int16)
		return (new Operand<short>(static_cast<short>(stoi(value))));
	if (type == Int32)
		return (new Operand<int>(stoi(value)));
	if (type == Float)
		return (new Operand<float>(stof(value)));
	if (type == Double)
		return (new Operand<double>(stod(value)));*/
}

IOperand const * OperandFactory::createInt8(std::string const & value) const {}
IOperand const * OperandFactory::createInt16(std::string const & value) const {}
IOperand const * OperandFactory::createInt32(std::string const & value) const {}
IOperand const * OperandFactory::createFloat(std::string const & value) const {}
IOperand const * OperandFactory::createDouble(std::string const & value) const {}