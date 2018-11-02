
#include "IOperand.hpp"
#include "Operand.hpp"
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
}

IOperand const * OperandFactory::createInt8(std::string const & value) const
{
	int stoiVal;
	try
	{
		stoiVal = stoi(value);
		if (stoiVal > INT8_MAX || stoiVal < INT8_MIN)
			throw OutOfRangeException(value, "Int8");
		return new Operand<char>(static_cast<char>(stoiVal));
	}
	catch (const std::out_of_range&)
	{
		throw OutOfRangeException(value, "Int8");
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidArgumentException(value, "Int8");
	}
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	int stoiVal;
	try
	{
		stoiVal = stoi(value);
		if (stoiVal > INT16_MAX || stoiVal < INT16_MIN)
			throw OutOfRangeException(value, "Int16");
		return new Operand<short>(static_cast<short>(stoiVal));
	}
	catch (const std::out_of_range&)
	{
		throw OutOfRangeException(value, "Int16");
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidArgumentException(value, "Int16");
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
		throw OutOfRangeException(value, "Int32");
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidArgumentException(value, "Int32");
	}
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	float stofVal;
	try
	{
		stofVal = stof(value);
		return new Operand<float>(stofVal);
	}
	catch (const std::out_of_range&)
	{
		throw OutOfRangeException(value, "Float");
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidArgumentException(value, "Float");
	}
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	double stodVal;
	try
	{
		stodVal = stod(value);
		return new Operand<double>(stodVal);
	}
	catch (const std::out_of_range&)
	{		
		throw OutOfRangeException(value, "Double");
	}
	catch (const std::invalid_argument&)
	{
		throw InvalidArgumentException(value, "Double");
	}
}

/* EXCEPTIONS */

// OutOfRange

OperandFactory::OutOfRangeException::OutOfRangeException(){}
OperandFactory::OutOfRangeException::OutOfRangeException(std::string value, std::string  type):
	_value(value),
	_type(type)
	{
		_msg = "Value " + _value + " overflows " + _type;
	}
OperandFactory::OutOfRangeException::OutOfRangeException(OutOfRangeException const &ref){*this = ref;}
OperandFactory::OutOfRangeException &OperandFactory::OutOfRangeException::operator=(OutOfRangeException const &ref)
{
	exception::operator=(ref);
	return *this;
}
OperandFactory::OutOfRangeException::~OutOfRangeException() throw() {}
const char* OperandFactory::OutOfRangeException::what() const throw()
{
	return _msg.c_str();
}

// InvalidArg

OperandFactory::InvalidArgumentException::InvalidArgumentException(){}
OperandFactory::InvalidArgumentException::InvalidArgumentException(std::string value, std::string  type) :
	_value(value),
	_type(type)
{
	_msg = "Value " + _value + " overflows " + _type;
}
OperandFactory::InvalidArgumentException::InvalidArgumentException(InvalidArgumentException const &ref){*this = ref;}
OperandFactory::InvalidArgumentException &OperandFactory::InvalidArgumentException::operator= (InvalidArgumentException const &ref)
{
	exception::operator=(ref);
	return *this;
}
OperandFactory::InvalidArgumentException::~InvalidArgumentException() throw() {}
const char* OperandFactory::InvalidArgumentException::what() const throw()
{
	return _msg.c_str();
}
