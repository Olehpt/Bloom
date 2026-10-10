#include "bloom_class.h"

double Bloom::read_from_file(const std::string& filename) {
	std::ifstream file(filename);
	size_t counter = 0;
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return -1;
	}
	auto start = std::chrono::high_resolution_clock::now();
	std::string line, op;
	while (file >> op >> line) {
		if (op == "+") {
			write(line);
		}
		else if (op == "?") {
			if (find(line)) counter++;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	double result = std::chrono::duration<double>(end - start).count();
	std::cout << "Multiple hashing. Time taken to read from file: " << result << " seconds" << std::endl;
	file.close();
	return result;
}

double Bloom::read_from_file_p(const std::string& filename) {
	std::ifstream file(filename);
	size_t counter = 0;
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return -1;
	}
	auto start = std::chrono::high_resolution_clock::now();
	std::string line, op;
	while (file >> op >> line) {
		if (op == "+") {
			write_p(line);
		}
		else if (op == "?") {
			if (find_p(line)) counter++;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	double result = std::chrono::duration<double>(end - start).count();
	file.close();
	return result;
}