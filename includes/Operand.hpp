
#pragma once

#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "defines.hpp"
#include <iostream>
#include <string>
#include <cfloat>
#include <cmath>

template <typename T>
class Operand : public IOperand
{
public:
	//Canonical
	Operand<T>(void) : _value(0)
	{
		defineTType();
		setStringValue();
	}
	Operand<T>(T const value) : _value(value)
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
	~Operand<T>() {}
	//getters
	int getPrecision(void) const
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
		if (maxType < Float)
			return _of.createOperand(maxType, std::to_string((int)c));
		return _of.createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator-(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		long double c = a - b;
		if (maxType < Float)
			return _of.createOperand(maxType, std::to_string((int)c));
		return _of.createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator*(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		long double c = a * b;
		if (maxType < Float)
			return _of.createOperand(maxType, std::to_string((int)c));
		return _of.createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator/(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		if (b == 0.0)
			throw OperationException("Division by zero");
		long double c = a / b;
		if (maxType < Float)
			return _of.createOperand(maxType, std::to_string((int)c));
		return _of.createOperand(maxType, std::to_string(c));
	}
	IOperand const * operator%(IOperand const & ref) const
	{
		eOperandType maxType = getMaxType(*this, ref);
		long double a = _value;
		long double b = stold(ref.toString());
		if (b == 0.0)
			throw OperationException("Modulo by zero");
		long double c = std::fmod(a, b);
		if (maxType < Float)
			return _of.createOperand(maxType, std::to_string((int)c));
		return _of.createOperand(maxType, std::to_string(c));
	}
	//tools
	std::string const & toString(void) const
	{
		return _toString;
	}
	void printValue(void) const
	{
		if (_type==Int8)
			cout<<(int)_value;
		else
			cout<<_value;
	}
	eOperandType getMaxType(Operand<T> const &ref1, IOperand const &ref2) const
	{
		if (ref1.getPrecision() > ref2.getPrecision())
			return ref1.getType();
		return ref2.getType();
	}
	//exception
	class OperationException : public exception
	{
	public:
		OperationException() {}
		OperationException(std::string msg) : _msg(msg) {}
		OperationException(OperationException const &ref) { *this = ref; }
		OperationException &operator=(OperationException const &ref)
		{
			exception::operator=(ref);
			return *this;
		}
		~OperationException() throw() {}
		virtual const char* what() const throw()
		{
			return _msg.c_str();
		}
	private:
		std::string _msg;
	};


private:
	void defineTType(void)
	{
		static const std::map<std::string, eOperandType> _strToEOpMap =
		{
			{ typeid(char).name(), Int8 },
			{ typeid(short).name(), Int16 },
			{ typeid(int).name(), Int32 },
			{ typeid(float).name(), Float },
			{ typeid(double).name(), Double }
		};
		_type = _strToEOpMap.at(typeid(T).name());
	}
	void setStringValue(void)
	{
		_toString = std::to_string(_value);
		if (_toString.find(".") == std::string::npos)
			return;
		_toString.erase(_toString.find_last_not_of("0") + 1);
		if (_toString[_toString.length()-1]=='.')
			_toString.erase(_toString.end()-1,_toString.end());		
	}

	eOperandType			_type;
	T						_value;
	std::string				_toString;
	static const OperandFactory _of;
};

template <typename T>
const OperandFactory Operand<T>::_of = OperandFactory();
