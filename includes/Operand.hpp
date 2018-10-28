
#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "eOperandType.hpp"
#include "IOperand.hpp"
#include "defines.hpp"

//todo: tons of exceptions

template <typename T>
class Operand : public IOperand
{
public:
	//Canonical
	Operand<T>(void): _value(0)
	{
		string typeName = typeid(T).name();
		defineTType(typeName);
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
		this->_type = ref.getType();
		this->_value = ref.getValue();
		this->_toString = ref.toString();
	}
	~Operand<T>(){}
	//getters
	int getPrecision( void ) const
	{
		return sizeof(T);
	}
	eOperandType getType(void) const
	{
		return _type;
	}
	T getValue(void) const
	{
		return _value;
	}
	//tostring
	string const & toString( void ) const
	{
		return _toString;
	}
private:
	void defineTType(string typeName)
	{
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
	string			_toString;
};

#endif
