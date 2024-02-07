#include <iostream>
#include "evox.h"

int main(int argc, const char **argv) {
	std::cout << "Result is " << evox("((2+1)*4)/3") << std::endl;
	return 0;
}
