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

	auto t1 = b.read_from_file("_init.txt");
	auto t2 = b.read_from_file("_ops.txt");

	float r1 = b.ratio();
	std::cout << "Ratio 1: " << r1 << "\n";

	std::cout << "Time 1: " << t1 << "\n";
	std::cout << "Time 2: " << t2 << "\n";

	b.reset();

	auto t21 = b.read_from_file_p("_init.txt");
	auto t22 = b.read_from_file_p("_ops.txt");

	float r2 = b.ratio();
	std::cout << "Ratio 2: " << r2 << "\n";

	std::cout << "Time 21: " << t21 << "\n";
	std::cout << "Time 22: " << t22 << "\n";

	b.reset();

	b.check_false_triggers("_init.txt", "_ops.txt");
	b.check_false_triggers_p("_init.txt", "_ops.txt");
}