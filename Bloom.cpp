#include <iostream>
#include "bloom_class.h"
#include "generator.h"

int main()
{
	const float p = 0.01;
	const long t_size = 10e5, a_size = 9583333;

	//generate("_init.txt", 10e5, '+');
	//generate("_ops.txt", 10e4, '?');

	Bloom b(a_size);
}