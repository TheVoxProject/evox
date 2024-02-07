#include "evox.h"

double evox(const std::string& expression) {
	std::stack<double> numbers;
	std::stack<char> operators;
	bool reading_number = false;
	double current_number = 0;
	for (char c : expression) {
		if (isdigit(c)) {
			if (reading_number) {
				current_number = current_number * 10 + (c - '0');
			} else {
				current_number = c - '0';
				reading_number = true;
			}
		} else {
			if (reading_number) {
				numbers.push(current_number);
				current_number = 0;
				reading_number = false;
			}
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
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
					operators.pop();
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
	}
	if (reading_number) {
		numbers.push(current_number);
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
