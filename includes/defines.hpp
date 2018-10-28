
#ifndef DEFINES_H
# define DEFINES_H

#include <iostream>
#include <iomanip>

#define cout std::cout
#define cin std::cin
#define endl std::endl
#define string std::string
#define getline std::getline
#define max(x, y) x < y ? y : x
#define min(x, y) x > y ? y : x

typedef struct	s_data
{
	string	paramname;
	int		value;
}				t_data;

#endif
