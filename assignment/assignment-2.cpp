/* This c++ program provides a way to store and manipulate expressions written
* in either infix or postfix notation. For example, 

a+b*c+(d*e+f)*g (infix) is equivalent to abc*+de*f+g*+ (postfix)

* To complete this assignment I use the in-class pdf_files and these two following websites:
* https://prepinsta.com/cpp-program/infix-to-postfix-conversion-using-stack/
* https://www.prepbytes.com/blog/stacks/infix-to-postfix-conversion-using-stack/
*/


#include <iostream>
#include <string>
#include <stack>
using namespace std;



/*
* This program implements an Expression class that contains 
* a constructor and three methods. The Expression class is used to store and manipulate 
* expressions written in either infix or postfix notation. The class contains two private 
* string variables, one to store the infix expression and one to store the postfix expression.
*/ 

class Expression {

public:

    Expression(string input, int direction); // constructor

    string inToPost(); // method to transform the local infix expression to postfix

    string postToIn(); // method to transform the local postfix expression to infix

    double evaluate(); // method to evaluate the expression



private:

    string infix; // private string variable to store the infix expression

    string postfix; // private string variable to store the postfix expression

};



// constructor to initialize the infix/postfix expression and the direction

Expression::Expression(string input, int direction) {

    if (direction == 1) 

        infix = input;

    else if(direction == 2) 

        postfix = input;

}



// inToPost() method

string Expression::inToPost() {

    stack<char> s;

    string postfix = ""; // initialize postfix as empty string

    for (int i = 0; i<infix.length(); i++) {

        // If the scanned character is an operand, add it to output.

        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))

            postfix+= infix[i];

 

        // If the scanned character is an '(', push it to the stack.

        else if (infix[i] == '(')

            s.push('(');

 

        //  If the scanned character is an ')', pop and output from the stack

        // until an '(' is encountered.

        else if (infix[i] == ')') {

            while (s.top() != '(') {

                postfix += s.top();

                s.pop();

            }

            s.pop();

        }

 

        //If an operator is scanned

        else {

            while (!s.empty() && s.top() != '(' && (infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-')) {

                postfix += s.top();

                s.pop();

            }

            s.push(infix[i]);

        }

    }

 

    //Pop all the remaining elements from the stack

    while (!s.empty()) {

        postfix += s.top();

        s.pop();

    }

    return postfix;

}



// postToIn() method

string Expression::postToIn() {

    stack<string> s;

    for (int i = 0; i<postfix.length(); i++) {

 

        // If the scanned character is an operand (number here),

        // push it to the stack.

        if ((postfix[i] >= 'a' && postfix[i] <= 'z') || (postfix[i] >= 'A' && postfix[i] <= 'Z'))

            s.push(string(1, postfix[i]));

 

        //  If the scanned character is an operator, pop two

        // elements from stack apply the operator

        else {

            string val1 = s.top();

            s.pop();

            string val2 = s.top();

            s.pop();

            string temp = "(" + val2 + postfix[i] + val1 + ")";

            s.push(temp);

        }

    }

 

    // There must be a single element in stack now which is the result

    return s.top();

}



// evaluate() method takes the local postfix expression and returns the value of the expression.

double Expression::evaluate() {

    stack<double> s;

    for (int i = 0; i<postfix.length(); i++) {

        // If the scanned character is an operand (number here),

        // push it to the stack.

        if ((postfix[i] >= 'a' && postfix[i] <= 'z') || (postfix[i] >= 'A' && postfix[i] <= 'Z'))

            s.push(postfix[i] - '0');

        //  If the scanned character is an operator, pop two

        // elements from stack apply the operator

        else {

            double val1 = s.top();

            s.pop();

            double val2 = s.top();

            s.pop();

            switch (postfix[i]) {

            case '+':

                s.push(val2 + val1);

                break;

            case '-':

                s.push(val2 - val1);

                break;

            case '*':

                s.push(val2 * val1);

                break;

            case '/':

                s.push(val2 / val1);

                break;

            }

        }

    }

    return s.top();

}



/* The main() function of the program displays a prompt to the user,
* allowing them to enter an expression in either infix or postfix notation to be 
* transformed to the other and evaluated. */

/* The program then creates an Expression object, passing the user input and the direction
* as parameters to the constructor. The program then checks the direction and if it is 1, 
* it calls the inToPost() method to convert the infix expression to postfix. If the direction is 2, 
* the postToIn() method is called to convert the postfix expression to infix. Finally, the evaluate() 
* method is called to evaluate the expression.
*/

int main() {

    string input;

    int direction;

    cout << "Enter expression in infix or postfix notation: ";

    cin >> input;

    cout << "Enter direction (1 for infix to postfix, 2 for postfix to infix): ";

    cin >> direction;

    Expression expression(input, direction);

    if (direction == 1)

        cout << "Postfix: " << expression.inToPost() << endl;

    else if (direction == 2)

        cout << "Infix: " << expression.postToIn() << endl;

    cout << "Evaluate expression: " << expression.evaluate() << endl;

    return 0;

}
