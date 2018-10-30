
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
OperandFactory & OperandFactory::operator=(const OperandFactory&) { return *this; }
OperandFactory::~OperandFactory() {}

/* Factory*/
IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	return (this->*createFuncs[type])(value);
	/*if (type == Int8)
		return (new Operand<char>());
	if (type == Int16)
		return (new Operand<short>(static_cast<short>(stoi(value))));
	if (type == Int32)
		return (new Operand<int>(stoi(value)));
	if (type == Float)
		return (new Operand<float>(stof(value)));
	if (type == Double)
		return (new Operand<double>(stod(value)));*/
}

IOperand const * OperandFactory::createInt8(std::string const & value) const
{
	int stoiVal;
	try
	{
		stoiVal = stoi(value);
		if (stoiVal > INT8_MAX || stoiVal < INT8_MIN)
			throw;
		return new Operand<char>(static_cast<char>(stoiVal));
	}
	catch (const std::out_of_range&)
	{
		cout << "Value " << value << " overflows Int8" << endl;
		//throw custom exception here
	}
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	int stoiVal;
	try
	{
		stoiVal = stoi(value);
		if (stoiVal > INT16_MAX || stoiVal < INT16_MIN)
			throw;
		return new Operand<short>(static_cast<short>(stoiVal));
	}
	catch (const std::out_of_range&)
	{
		cout << "Value " << value << " overflows Int16" << endl;
		//throw custom exception here
	}
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
	int stoiVal;
	try
	{
		stoiVal = stoi(value);
		return new Operand<int>(stoiVal);
	}
	catch (const std::out_of_range&)
	{
		cout << "Value " << value << " overflows Int32" << endl;
		//throw custom exception here
	}
	//todo: catch invalid argument exc
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	int stofVal;
	try
	{
		stofVal = stof(value);
		return new Operand<float>(stofVal);
	}
	catch (const std::out_of_range&)
	{
		cout << "Value " << value << " overflows float" << endl;
		//throw custom exception here
	}
	//todo: catch invalid argument exc
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	int stodVal;
	try
	{
		stodVal = stod(value);
		return new Operand<double>(stodVal);
	}
	catch (const std::out_of_range&)
	{
		cout << "Value " << value << " overflows double" << endl;
		//throw custom exception here
	}
	//todo: catch invalid argument exc
}