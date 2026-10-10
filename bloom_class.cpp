#include "bloom_class.h"

Bloom::Bloom(unsigned long a_size) : actual_size(a_size) {
	bits = std::vector<bool>(actual_size, 0);
}

unsigned long Bloom::hash_p(const std::string& s, int p) {
	unsigned long hash = 0;
	for (unsigned char c : s) {
		hash = (hash * p + c) % actual_size;
	}
	return hash;
}

void Bloom::write(const std::string& s) {
	unsigned long h1 = hash_p(s, prs_[0]);
	unsigned long h2 = hash_p(s, prs_[1]);
	for (size_t i = 1; i < 7; i++) {
		unsigned long h = (h1 + i * h2) % actual_size;
		bits[h] = 1;
	}
}

void Bloom::write_p(const std::string& s) {
	for (int p : prs) {
		unsigned long h = hash_p(s, p);
		bits[h] = 1;
	}
}

bool Bloom::find(const std::string& s) {
	unsigned long h1 = hash_p(s, prs_[0]);
	unsigned long h2 = hash_p(s, prs_[1]);
	for (size_t i = 1; i < 7; i++) {
		unsigned long h = (h1 + i * h2) % actual_size;
		if (!bits[h]) {
			return 0;
		}
	}
	return 1;
}

bool Bloom::find_p(const std::string& s) {
	for (int p : prs) {
		unsigned long h = hash_p(s, p);
		if (!bits[h]) {
			return 0;
		}
	}
	return 1;
}

void Bloom::reset() {
	bits = std::vector<bool>(actual_size, 0);
}