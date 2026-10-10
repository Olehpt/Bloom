#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

const int prs[] = { 31, 37, 41, 43, 47, 53};
const int prs_[] = { 31, 7727 };

class Bloom {
	unsigned long actual_size;
	std::vector<bool> bits;
public:
	Bloom(unsigned long a_size);
	unsigned long hash_p(const std::string& s, int p);
	
	void write(const std::string& s);
	void write_p(const std::string& s);
	bool find(const std::string& s);
	bool find_p(const std::string& s);

	void reset();
	double read_from_file(const std::string& filename);
	double read_from_file_p(const std::string& filename);

	bool check_false_triggers(const std::string& filename_init, const std::string& filename_ops);
	bool check_false_triggers_p(const std::string& filename_init, const std::string& filename_ops);
};