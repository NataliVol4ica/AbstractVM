
#pragma once

#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "defines.hpp"
#include <iostream>
#include <string>

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
	/*IOperand const * operator+( IOperand const & rhs ) const
	{
		//Operand<T> = 
	}*/
	//tools
	std::string const & toString( void ) const
	{
		return _toString;
	}
	eOperandType getMaxType(IOperand const &ref1, IOperand const &ref2)
	{
		if (ref1.getPrecision() > ref2.getPrecision())
			return ref1.getType();
		return ref2.getType();
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

	eOperandType	_type;
	T				_value;
	std::string		_toString;
};
