#include <iostream>
#include <string>
#include "evox.h"

int main(int argc, const char **argv) {
	while (true) {
		try {
			std::string expression;
			std::cout << "Enter expression:";
			getline(std::cin, expression);
			if (expression == "") break;
			std::cout << evox(expression) << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return 0;
}
