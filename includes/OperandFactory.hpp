
#pragma once

#include "Operand.hpp"
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

private:

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	typedef IOperand const* (OperandFactory::*func)(std::string const & value) const;
	static func createFuncs[];
};