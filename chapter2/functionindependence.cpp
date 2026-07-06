#include <iostream>

using namespace std;



// 4. Function Independence
// Function independence is the design principle that ensures functions are self-contained and do not rely on external state or variables.
// Each function should perform a specific task and can be tested and maintained independently. The advantages of function independence include easier debugging, improved code readability, and enhanced maintainability.





class Operations {


    // Independent Module 1: Handles basic arithmetic operations
    public: 


       // Each function is self-contained and does not rely on external state or variables
       int add(int a, int b) {
            return a + b;
        }

        // Each function is self-contained and does not rely on external state or variables
        int subtract(int a, int b) {
            return a - b;
        }

        int multiply(int a, int b) {
            return a * b;
        }

        double divide(int a, int b) {
            if (b != 0) {
                return static_cast<double>(a) / b;
            } else {
                cerr << "Error: Division by zero is not allowed." << endl;
                return 0; 
            }
        }
};



int main(){


    int num1 = 10;
    int num2 = 5;


    Operations ops;

    cout << "Addition: " << ops.add(num1, num2) << endl;
    cout << "Subtraction: " << ops.subtract(num1, num2) << endl;
    cout << "Multiplication: " << ops.multiply(num1, num2) << endl;
    cout << "Division: " << ops.divide(num1, num2) << endl;


    return 0;

}
