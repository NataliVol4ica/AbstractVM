
#pragma once

#include <iostream>
#include <iomanip>

#define cout std::cout
#define cin std::cin
#define endl std::endl
#define max(x, y) x < y ? y : x
#define min(x, y) x > y ? y : x

typedef struct	s_data
{
	std::string	paramname;
	int			value;
}				t_data;
