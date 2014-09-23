#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <stdio.h>

class NoneCopyable
{

};

class Operation : public NoneCopyable
{
public:
	Operation() : m_number1(.0), m_number2(.0) { }
	virtual ~Operation() {}
	double m_number1;
	double m_number2;
	virtual double GetResult() const = 0;
};

class OperationAdd : public Operation
{
	virtual double GetResult() const
	{
		return m_number1 + m_number2;
	}
};

class OperationSub : public Operation
{
	virtual double GetResult() const
	{
		return m_number1 - m_number2;
	}
};

class OperationMul : public Operation
{
	virtual double GetResult() const
	{
		return m_number1 * m_number2;
	}
};

class OperationDiv : public Operation
{
	virtual double GetResult() const
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
	return val >= 1 && val <= 10000000;
}

int main(int argc, char* argv[])
{
	int a = 0;
	int b = 0;
	char op = 0;
	std::string line;
	std::getline(std::cin, line);
	for (size_t i = 0; i != line.size(); i++) {
		char c = line[i];
		if (c == '\t')
			return 0;
	}
	int ret = sscanf(line.c_str(), "%d %c %d", &a, &op, &b);
	if (ret == 0 || ret == EOF) {
		return 0;
	}
	if (!is_valid_value(a) || !is_valid_value(b)) {
		//std::cout << "You must input 2 positive integers." << std::endl;
	} else {
		Operation *operation = OperationFactory::CreateOperation(op);
		if (operation) {
			operation->m_number1 = a;
			operation->m_number2 = b;
			double result = operation->GetResult();
			std::cout << static_cast<int>(result) << std::endl;
			delete operation;
		} else {
			//std::cout << "Illegal expression." << std::endl;
		}
		
	}
	//getchar();
	return 0;
}