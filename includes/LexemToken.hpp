
#pragma once

#include "eLexemType.hpp"

struct LexemToken
{
	std::string str;
	eLexemType type;
	LexemToken(std::string sstr, eLexemType ttype) : str(sstr), type(ttype) {}
};