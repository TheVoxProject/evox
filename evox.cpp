#include "evox.h"

// Evaluates basic math expressions. Currently nothing advanced is supported, it's basically a four-function calculator. It'll need some refactoring to grow, but it's still quite doable, and planned.
double evox(const std::string& expression) {
	std::stack<double> numbers;
	std::stack<char> operators;
	for (char c : expression) {
		if (isdigit(c)) {
			// Stupid and weird hack to convert a char to an int without a cast.
			numbers.push(c - '0');
		} else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			while (!operators.empty() && operators.top() != '(' && (c == '^' || c == '*' || c == '/' || c == '+' || c == '-')) {
				char op = operators.top();
				double operand2 = numbers.top();
				numbers.pop();
				double operand1 = numbers.top();
				numbers.pop();
				switch (op) {
				case '+':
					numbers.push(operand1 + operand2);
					break;
				case '-':
					numbers.push(operand1 - operand2);
					break;
				case '*':
					numbers.push(operand1 * operand2);
					break;
				case '/':
					numbers.push(operand1 / operand2);
					break;
				case '^':
					numbers.push(pow(operand1, operand2));
					break;
				}
			}
			operators.push(c);
		} else if (c == '(') {
			operators.push(c);
		} else if (c == ')') {
			while (!operators.empty() && operators.top() != '(') {
				char op = operators.top();
				operators.pop();
				double operand2 = numbers.top();
				numbers.pop();
				double operand1 = numbers.top();
				numbers.pop();
				switch (op) {
				case '+':
					numbers.push(operand1 + operand2);
					break;
				case '-':
					numbers.push(operand1 - operand2);
					break;
				case '*':
					numbers.push(operand1 * operand2);
					break;
				case '/':
					numbers.push(operand1 / operand2);
					break;
				case '^':
					numbers.push(pow(operand1, operand2));
					break;
				}
			}
			operators.pop();
		}
	}
	while (!operators.empty()) {
		char op = operators.top();
		operators.pop();
		double operand2 = numbers.top();
		numbers.pop();
		double operand1 = numbers.top();
		numbers.pop();
		switch (op) {
		case '+':
			numbers.push(operand1 + operand2);
			break;
		case '-':
			numbers.push(operand1 - operand2);
			break;
		case '*':
			numbers.push(operand1 * operand2);
			break;
		case '/':
			numbers.push(operand1 / operand2);
			break;
		case '^':
			numbers.push(pow(operand1, operand2));
			break;
		}
	}
	return numbers.top();
}
