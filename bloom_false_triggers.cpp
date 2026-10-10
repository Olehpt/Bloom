#include "bloom_class.h"
#include <unordered_set>

bool Bloom::check_false_triggers(const std::string& filename_init, const std::string& filename_ops) {
	size_t false_positives = 0;
	size_t false_negatives = 0;
	size_t negative_queries = 0;

	this->reset();

	std::ifstream file(filename_init);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename_init << std::endl;
		return 0;
	}

	std::unordered_set<std::string> added_elements;

	std::string line, op;
	while (file >> op >> line) {
		if (op == "+") {
			write(line);
			added_elements.insert(line);
		}
	}
	
	file.close();
	file = std::ifstream(filename_ops);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename_ops << std::endl;
		return 0;
	}

	while (file >> op >> line) {
		if (op == "?") {
			bool actual = added_elements.contains(line);
			bool res = this->find(line);

			if (!actual) {
				negative_queries++;
				if (res) {
					false_positives++;
				}
			}
			else {
				if (!res) {
					false_negatives++;
				}
			}
		}
	}

	double rate = negative_queries
		? double(false_positives) / negative_queries
		: 0.0;

	std::cout << "False positives: " << false_positives << '\n';
	std::cout << "False negatives: " << false_negatives << '\n';
	std::cout << "False positive rate: " << rate * 100 << "%\n";

	return 1;
}

bool Bloom::check_false_triggers_p(const std::string& filename_init, const std::string& filename_ops) {
	size_t false_positives = 0;
	size_t false_negatives = 0;
	size_t negative_queries = 0;

	this->reset();

	std::ifstream file(filename_init);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename_init << std::endl;
		return 0;
	}

	std::unordered_set<std::string> added_elements;

	std::string line, op;
	while (file >> op >> line) {
		if (op == "+") {
			write_p(line);
			added_elements.insert(line);
		}
	}

	file.close();
	file = std::ifstream(filename_ops);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename_ops << std::endl;
		return 0;
	}

	while (file >> op >> line) {
		if (op == "?") {
			bool actual = added_elements.contains(line);
			bool res = this->find_p(line);

			if (!actual) {
				negative_queries++;
				if (res) {
					false_positives++;
				}
			}
			else {
				if (!res) {
					false_negatives++;
				}
			}
		}
	}

	double rate = negative_queries
		? double(false_positives) / negative_queries
		: 0.0;

	std::cout << "False positives: " << false_positives << '\n';
	std::cout << "False negatives: " << false_negatives << '\n';
	std::cout << "False positive rate: " << rate * 100 << "%\n";

	return 1;
}