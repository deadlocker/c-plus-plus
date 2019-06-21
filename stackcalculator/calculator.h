#ifndef CALCULATOR_H
#define CALCULATOR_H



#include <iostream>
#include <string>
#include <cmath>
#include <bits/basic_string.h>
#include "Stack.h"
using namespace std;

class Calculator
{
private:
	/**
	 * This function will help in finding the precedence of operator
	 */
	int precedence(char);

	/**
	 * This function will help replacing negative sign with n.
	 */
	std::string findNegative(std::string);

	/**
	 * This functionn will infix_to_postfixs infix to postfix expression
	 */
	
	std::string infix_to_postfix(std::string);

	/** 
	 * THis function evaluates the postfix expression using own stack
	 */
	std::string evaluate(std::string);

	/** 
	 * This function performs a calculation
	 */
	std::string evaluate_infix(std::string);

	/** 
	 * This function will display menu options for calculation
	 */
	void menuBar();

	/**
	 * This function will test if the expression has matching parenthesis or not
	 */ 
	bool checkparanthesis(const std::string&);

	/**
	 * This  function will remove unnecessary spaces
	 */ 
	void removeSpace(std::string&);

	/** 
	 * This function will test if expression is single number
	 */
	bool singleNumber(std::string);

public:

	/**
	 * constructor
	 */
    Calculator();

    /**
     * destructor
     */ 
    ~Calculator();

    /**
     * This is the function to start calculator functioning
     */ 
	void start();

};

/** 
 * here we have required definitions of all the  functions
 */ 


/**
 * This function will determine the precedence of a input operator
 */ 
int Calculator::precedence(char ch) {
	if(ch == '+' || ch == '-') {
		return 1;
	} else if(ch == '*' || ch == '/' || ch == '%') {
		return 2;
	} else {
		return 0;
	}
}

/** 
 * This function will take precedence of opreator and check it
 */
 
bool TakesPrecedence(char OperatorA, char OperatorB)
{
   if (OperatorA == '(')
      return false;
   else if (OperatorB == '(')
      return false;
   else if (OperatorB == ')')
      return true;
   else if ((OperatorA == '^') && (OperatorB == '^'))
      return false;
   else if (OperatorA == '^')
      return true;
   else if (OperatorB == '^')
      return false;
   else if ((OperatorA == '*') || (OperatorA == '/'))
      return true;
   else if ((OperatorB == '*') || (OperatorB == '/'))
      return false;
   else
      return true;
       
}
 
/**
 * This function will replace negative sgns with 'n'
 */
 
std::string Calculator::findNegative(std::string myString) {
	char c = ' ';

	for(size_t i = 0; i < myString.size() - 1; ++i) {
		if(myString[i] == '-') {
			if(i == 0) {
				myString[i] = 'N';
				if(myString[i + 1] == '(') {
					myString.insert(i + 1, "1*");
					i += 2;
				}
			} else {
				c = myString[i - 1];
				if(c == '+' || c == '-' || c == '*' || c == '(') {
					myString[i] = 'N';
					if(myString[i + 1] == '(') {
						myString.insert(i + 1, "1*");
						i += 2;
					}
				} else if(c == '/') {
					myString[i] = 'N';
					if(myString[i + 1] == '(') {
						myString.insert(i + 1, "1/");
						i += 2;
					}
				} else if(c == '%') {
					myString[i] = ' ';
				}
			}
		}
	}

	std::cout << myString << "\n";
	return myString;
}


/**
 * This function will help to solve infix expression to postfix expression
 */
 
std::string Calculator::infix_to_postfix(std::string infix) {
	size_t end = infix.size();
	Stack<char> data(end);

	std::string postfix = "";

	char c = ' ';
	char d = ' ';

	for(size_t i = 0; i < end; ++i) {
		c = infix[i];
		switch(c) {
			case '0': case '1':
            case '2': case '3':
            case '4': case '5':
            case '6': case '7':
            case '8': case '9':
            case ' ': case 'N': {
                postfix += c;
                break;
            }

            case '(': {
            	data.push(c);
            	break;
            }

            case '+': case '-':
            case '*': case '/':
            case '%': {
            	postfix += " ";
            	while(!data.is_empty() &&
            		  data.top() != '(' &&
            		  precedence(c) <= precedence(data.top())) {

            		postfix += data.top();
            		postfix +=  " ";
            		data.pop();
            	}

            	data.push(c);
            	break;
            }

            case ')': {
				while(data.top() != '(') {
					postfix += " ";
					postfix += data.top();
            		data.pop();
            	}

            	data.pop();
				break;
			}
		}
	}

	while(!data.is_empty()) {
        postfix += " ";
		postfix += data.top();
		data.pop();
	}

	std::cout << postfix << "\n";
	return postfix;
}

/**
 * This function will help to evaluate post fix expression 
 */
 
std::string Calculator::evaluate(std::string postfix) {
	size_t end = postfix.size();
	Stack<int> data(end);

	std::string number_string = "";
	char c = ' ';

	for(size_t i = 0; i < end; ++i) {
		c = postfix[i];
		switch(c) {
			case 'N': {
				number_string += '-';
				break;
			}

			case '0': case '1':
            case '2': case '3':
            case '4': case '5':
            case '6': case '7':
            case '8': case '9': {
                number_string += c;
                break;
            }

            case '+': case '-':
            case '*': case '/':
            case '%': {
            	if(number_string.size() > 0) {
            		data.push(std::stoi(number_string));
            		number_string = "";
            	}

				int op_1 = data.top();
				data.pop();

				int op_2 = data.top();
				data.pop();

				if(c == '+') data.push(op_2 + op_1);
				if(c == '-') data.push(op_2 - op_1);
				if(c == '*') data.push(op_2 * op_1);
				if(c == '/') data.push(op_2 / op_1);
				if(c == '%') data.push(op_2 % op_1);

            	break;
            }

            case ' ': {
            	if(number_string.size() > 0) {
            		data.push(std::stoi(number_string));
            		number_string = "";
            	}

            	break;
            }
        }
	}

	return std::to_string(data.top());
}

/** 
 * This function will perform a calculation and return string
 */
 
std::string Calculator::evaluate_infix(std::string infix) {
	return evaluate(
		infix_to_postfix(
			findNegative(infix)
		)
	);
}

/**
 * This is function for menu bar displays options
 */
 
void Calculator::menuBar() {
	std::cout << "\n";
	std::cout << " For Menu -> M\n\n";
	std::cout << " For infix calculation -> i \n\n";
	std::cout << " For postfix calculation -> p\n\n";
	std::cout << " To quit the calculator application ->q\n\n";
}

/**
 * This boolean function wil test if expression has matching parentheses
 */
 
bool Calculator::checkparanthesis(const std::string& myString) {
	int end = myString.size();
	bool match = true;

	/**
	 * This is the stack for parentheses
	 */
	 
	Stack<char> p_stack(end);

	/**
	 * This will compare '(' to ')' in string
	 */
	 
	for(size_t i = 0; i < end; ++i) {
		if(myString[i] == '(') {
			p_stack.push(myString[i]);
		} else if(myString[i] == ')') {
			// if there is nothing on stack to pop,
			// we have mismatched parentheses
			if(!p_stack.pop()) match = false;
		}
	}

	/**
	 * if a '(' is left in the stack,  we have mismatched parentheses
	 */
	 
	if(!p_stack.is_empty()) match = false;

	 /**
	  * evaluate and return result
	  */ 
	return match;
}

/** 
 * This function will remove unwanted spaces so that extra space is not consumed in memory
 */
 
 
  void Calculator::removeSpace(std::string& myString) {
	int end = myString.size();

	/**
	 * This will move characters in front of spaces
	 */
	 
    for(int i = 0; i < end - 1; ++i) {
        if(myString[i] == ' ') {
            for(int j = i + 1; j < end; ++j) {
                if(myString[j] != ' ') {
                    myString[i] = myString[j];
                    myString[j] = ' ';
                    j = end;
                }
            }
        }
    }

    /** 
     * This function will count up to first space and check it
     */ 
    int counter = 0;
    for(int i = 0; i < end; ++i) {
        if(myString[counter] != ' ') {
            ++counter;
        }
    }

    /**
     * It will resize to remove space
     */
     
    myString.resize(counter);
    std::cout << "\n" << myString << "\n";
}

/**
 * This function will test if expression is single number or not
 */
 
bool Calculator::singleNumber(std::string myString) {
	size_t end = myString.size();
	bool only_a_number = true;
	char c = ' ';

	for(size_t i = 0; i < end; ++i) {
		c = myString[i];
		switch(c) {
            case '+': case '-':
            case '*': case '/':
            case '%': case '^': {
            	only_a_number = false;
            	break;
            }
        }
	}

	return only_a_number;
}



/**
 * default constructor
 */
 
Calculator::Calculator() {}

/**
 * destructor
 */
 
Calculator::~Calculator() {}

/**
 * This is the function to run calculator operations
 */
 
void Calculator::start() {
	std::string input = "";
	std::string mode = "infix";

	menuBar();

	bool done = false;
	while(!done) {

		std::cout << "Enter your answer: ";
		std::getline(std::cin, input);

		if(input == "q" || input == "Q") {
			std::cout << "\ncome back again!\n" << std::endl;
			done = true;
		} else if(input == "o" || input == "O") {
			menuBar();
		} else if(input == "i" || input == "I") {
			mode = "infix";
		} else if(input == "p" || input == "P") {
			mode = "postfix";
		} else {
			if(singleNumber(input)) {
				std::cout << "\n" << input << "\n" << std::endl;
			} else if(mode == "infix") {
				// remove_spaces(input);
				if(checkparanthesis(input)) {
					std::cout << "\n" << evaluate_infix(input) << "\n" << std::endl;
				} else {
					std::cout << "Try again paranthesis not balanaced." <<"\n" << std::endl;
				}

			} else {
				std::cout << "\n" << evaluate(input) << "\n" << std::endl;
			}
		}
	}
}


#endif
