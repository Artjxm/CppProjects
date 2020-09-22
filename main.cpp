#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>

bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isOperand(char c) {
	return isdigit(c);
}

int precedence (char c) {
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '-' || c == '+')
		return 1;
	else
		return -1;
}

std::string infixToPrefix(std::stack<char> stack, std::string infix) {
	std::string prefix;

	reverse(infix.begin(), infix.end());

	for (auto i = 0; i < infix.length(); ++i) {
		if (infix[i] == '(')
			infix[i] = ')';
		else if (infix[i] == ')')
			infix[i] = '(';
	}

	for (auto i = 0; i < infix.length(); ++i) {
		if (isOperand(infix[i]))
			prefix += infix[i];
		else if (infix[i] == '(')
			stack.push(infix[i]);
		else if (infix[i] == ')') {
			while (stack.top() != '(' && !stack.empty()) {
				prefix += stack.top();
				stack.pop();
			}

			if (stack.top() == '(')
				stack.pop();
		}
		else if (isOperator(infix[i])) {
			if (stack.empty())
				stack.push(infix[i]);
			else {
				if (precedence(infix[i]) > precedence(stack.top()))
					stack.push(infix[i]);
				else if ((precedence(infix[i]) == precedence(stack.top())) && infix[i] == '^') {
					while ((precedence(infix[i]) == precedence(stack.top())) && infix[i] == '^') {
						prefix += stack.top();
						stack.pop();
					}
					stack.push(infix[i]);
				}
				else if (precedence(infix[i]) == precedence(stack.top()))
					stack.push(infix[i]);
				else {
					while (!stack.empty() && precedence(infix[i]) < precedence(stack.top())) {
						prefix += stack.top();
						stack.pop();
					}
					stack.push(infix[i]);
				}
			}
		}
	}

	while (!stack.empty()) {
		prefix += stack.top();
		stack.pop();
	}

	std::reverse(prefix.begin(), prefix.end());

	return prefix;
}

int evaluatePrefix(std::string expr) {
	std::stack<int> stack;

	for (auto j = expr.length(); j >= 0; --j) {
		if (isOperand(expr[j]))
			stack.push(expr[j] - '0');
		else {
			int operand1 = stack.top();
			stack.pop();
			int operand2 = stack.top();
			stack.pop();

			switch (expr[j]) {
				case '+':
					stack.push(operand1 + operand2);
					break;
					case '-':
					stack.push(operand1 - operand2);
					break;
					case '*':
					stack.push(operand1 * operand2);
					break;
					case '/':
					stack.push(operand1 / operand2);
					break;
					case '^':
					stack.push(pow(operand1, operand2));
					break;
				default:
					break;
			}
		}
	}

	return stack.top();
}

int main() {
	std::string infix, prefix;

	std::cout << "Enter your infix expression, please: ";
	std::cin >> infix;

	std::stack <char> stack;
	prefix = infixToPrefix(stack, infix);

	std::cout << "\nYour expression but in prefix style: " << prefix;

	std::cout << "\nThe evaluated result is: " << evaluatePrefix(prefix);
}
