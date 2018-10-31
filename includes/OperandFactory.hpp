
#pragma once

#include "defines.hpp"
#include "IOperand.hpp"

//todo: canonic form

class OperandFactory
{
public:
	OperandFactory();
	OperandFactory(const OperandFactory &ref);
	OperandFactory& operator=(const OperandFactory &ref);
	IOperand const * createOperand(eOperandType type, std::string const & value) const;

	~OperandFactory();
	/* EXCEPTIONS */
	class OutOfRangeException : public exception
	{
	public:
		OutOfRangeException();
		OutOfRangeException(std::string value, eOperandType type);
		OutOfRangeException(OutOfRangeException const &ref);
		OutOfRangeException &operator=(OutOfRangeException const &ref);
		~OutOfRangeException() throw();
		virtual const char* what() const throw();
	private:
		std::string _value;
		eOperandType _type;
	};

private:

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	typedef IOperand const* (OperandFactory::*func)(std::string const & value) const;
	static func createFuncs[];
};