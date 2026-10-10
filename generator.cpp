#include "generator.h"

void generate(
    const std::string& filename,
    size_t count,
    char operation = 'r'
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<int> length_dist(1, 15);
    std::uniform_int_distribution<int> char_dist('a', 'z');
    std::uniform_int_distribution<int> op_dist(0, 1);

    for (size_t i = 0; i < count; i++) {
        char op = operation;

        if (operation == 'r') {
            op = op_dist(gen) == 0 ? '+' : '?';
        }

        int length = length_dist(gen);
        std::string word;

        for (int j = 0; j < length; j++) {
            word += static_cast<char>(char_dist(gen));
        }

        file << op << ' ' << word << '\n';
    }
}