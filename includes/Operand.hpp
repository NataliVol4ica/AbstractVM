
#pragma once

#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "defines.hpp"
#include <iostream>
#include <string>
#include <cfloat>

//todo: tons of exceptions

template <typename T>
class Operand : public IOperand
{
public:
	//Canonical
	Operand<T>(void): _value(0)
	{
		defineTType();
		setStringValue();
	}
	Operand<T>(T const value): _value(value)
	{
		defineTType();
		setStringValue();
	}
	Operand<T>(Operand<T> const &ref)
	{
		this->_type = ref.getType();
		this->_value = ref.getValue();
		this->_toString = ref.toString();
	}	
	Operand<T> &operator=(Operand<T> const &ref)
	{
		this->_value = ref.getValue();
		this->_toString = ref.toString();
	}
	~Operand<T>(){}
	//getters
	int getPrecision( void ) const
	{
		return static_cast<int>(_type);
	}
	eOperandType getType(void) const
	{
		return _type;
	}
	T getValue(void) const
	{
		return _value;
	}
	//operators
	IOperand const * operator+(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		long double c = a + b;
		//check if this check is necessary
		/*if (doesOverflow(maxType, c))
			//throw new exception: value does overflow maxtype
			;
		else*/
			return OperandFactory().createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator-(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		long double c = a - b;
		//check if this check is necessary
		/*if (doesOverflow(maxType, c))
			//throw new exception: value does overflow maxtype
			;
		else*/
			return OperandFactory().createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator*(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		long double c = a * b;
		//check if this check is necessary
		/*if (doesOverflow(maxType, c))
			//throw new exception: value does overflow maxtype
			;
		else*/
			return OperandFactory().createOperand(maxType, std::to_string(c));
	}
	//tools
	std::string const & toString( void ) const
	{
		return _toString;
	}
	eOperandType getMaxType(Operand<T> const &ref1, IOperand const &ref2) const
	{
		if (ref1.getPrecision() > ref2.getPrecision())
			return ref1.getType();
		return ref2.getType();
	}
	//todo: check if necessary
	bool doesOverflow(eOperandType type, long double val) const
	{
		switch (type)
		{
		case (Int8):
			return (val > INT8_MAX || val < INT8_MIN);
		case (Int16):
			return  (val > INT16_MAX || val < INT16_MIN);
		case (Int32):
			return (val > INT32_MAX || val < INT32_MIN);
		case (Float):
			return (val > FLT_MAX || val < -FLT_MAX);
		case (Double):
			return (val > DBL_MAX || val < -DBL_MAX);
		default:
			return true;
		}
	}
private:
	void defineTType(void)
	{
		std::string typeName = typeid(T).name();
		if (typeName == "c")
			_type = Int8;
		else if (typeName == "s")
			_type = Int16;
		else if (typeName == "i")
			_type = Int32;
		else if (typeName == "f")
			_type = Float;
		else 
			_type = Double;
	}
	void setStringValue(void)
	{		
		_toString = std::to_string(_value);
	}

	eOperandType			_type;
	T						_value;
	std::string				_toString;
	static OperandFactory	_of;
};
