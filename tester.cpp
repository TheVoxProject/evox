#include <iostream>
#include <string>
#include "evox.h"

int main(int argc, char **argv) {
	if (argc != 1) {
		try {
			std::string expression = argv[1];
			double result = evox(expression);
			std::cout << result << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}
	}
	else {
		while (true) {
			try {
				std::string expression;
				std::cout << "Enter expression (or press Enter to exit): ";
				std::getline(std::cin, expression);
				if (expression.empty()) break;
				std::cout << evox(expression) << std::endl;
			} catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
		return 0;
	}
}
