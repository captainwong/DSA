#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

class NoneCopyable
{

};

class Operation : public NoneCopyable
{
public:
	Operation() : m_number1(0), m_number2(0) { }
	virtual ~Operation() {}
	long long m_number1;
	long long m_number2;
	virtual long long  GetResult() const = 0;
};

class OperationAdd : public Operation
{
	virtual long long GetResult() const
	{
		return m_number1 + m_number2;
	}
};

class OperationSub : public Operation
{
	virtual long long GetResult() const
	{
		return m_number1 - m_number2;
	}
};

class OperationMul : public Operation
{
	virtual long long GetResult() const
	{
		return m_number1 * m_number2;
	}
};

class OperationDiv : public Operation
{
	virtual long long GetResult() const
	{
		if (m_number2 == 0) {
			return 0;
		} else {
			return m_number1 / m_number2;
		}
	}
};

class OperationFactory
{
public:
	static Operation* CreateOperation(char oper_char)
	{
		Operation *operation = NULL;
		switch (oper_char) {
			case '+':
				operation = new OperationAdd();
				break;
			case '-':
				operation = new OperationSub();
				break;
			case '*':
				operation = new OperationMul();
				break;
			case '/':
				//operation = new OperationDiv();
				break;
			default:
				break;
		}
		return operation;
	}
};

static inline bool is_valid_value(int val)
{
	return val >= 1 && val <= 1000000;
}

static inline bool my_is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static inline bool my_is_operand(char c)
{
	return c == '+' || c == '-' || c == '*';
}

int main(int argc, char* argv[])
{
	int a = 0;
	int b = 0;
	char op = 0;
	std::string line;
	std::getline(std::cin, line);
	std::string op1, op2, op3;
	int max_ops = 3;
	bool b_reading_val = false;
	for (size_t i = 0; i != line.size(); i++) {
		char c = line[i];
		if (c == '\t')
			return 0;
		else if (my_is_digit(c)) {
			b_reading_val = true;
			if (max_ops == 3) {
				op1 += c;
			} else if (max_ops == 2) {
				return 0;
			} else if (max_ops == 1) {
				op3 += c;
			} else if (max_ops == 0) {
				return 0;
			}
		} else if (my_is_operand(c)) {
			
			if (b_reading_val) {
				b_reading_val = false;
				max_ops--;
			}

			if (max_ops != 2) {
				return 0;
			}
			op2 = c;
			max_ops--;
		} else {
			if (b_reading_val) {
				b_reading_val = false;
				max_ops--;
			}
		}
	}
	//line >> a >> op >> b;
	/*int ret = sscanf(line.c_str(), "%d %c %d", &a, &op, &b);
	if (ret == 0 || ret == EOF) {
		return 0;
	}*/
	a = atoi(op1.c_str());
	op = op2.c_str()[0];
	b = atoi(op3.c_str());

	if (!is_valid_value(a) || !is_valid_value(b)) {
		//std::cout << "You must input 2 positive integers." << std::endl;
	} else {
		Operation *operation = OperationFactory::CreateOperation(op);
		if (operation) {
			operation->m_number1 = a;
			operation->m_number2 = b;
			long long result = operation->GetResult();
			std::cout << result << std::endl;
			delete operation;
		} else {
			//std::cout << "Illegal expression." << std::endl;
		}
		
	}
	//getchar();
	return 0;
}