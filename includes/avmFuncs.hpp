
#pragma once

#include "eOperandType.hpp"
#include "defines.hpp"
#include "IOperand.hpp"

IOperand const * createOperand(eOperandType type, std::string const & value );
