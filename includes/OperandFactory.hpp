
#pragma once

#include "defines.hpp"
#include "IOperand.hpp"

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
		OutOfRangeException(std::string value, std::string type);
		OutOfRangeException(OutOfRangeException const &ref);
		OutOfRangeException &operator=(OutOfRangeException const &ref);
		~OutOfRangeException() throw();
		virtual const char* what() const throw();
	private:
		std::string		_msg;
	};
	class InvalidArgumentException : public exception
	{
	public:
		InvalidArgumentException();
		InvalidArgumentException(std::string value, std::string type);
		InvalidArgumentException(InvalidArgumentException const &ref);
		InvalidArgumentException &operator=(InvalidArgumentException const &ref);
		~InvalidArgumentException() throw();
		virtual const char* what() const throw();
	private:
		std::string		_msg;
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

	//todo: replace array with map?