#include <iostream>
#include <string>
#include <memory>


// Interpreter Design Pattern
// Given a language, define a representation forits grammar along with an
// interpreterthat uses the representation to interpret sentences in the
// language.

// other example use case for interpreter design pattern:
// 1. Mathematical Expression Evaluator: An application that evaluates mathematical expressions can use the Interpreter pattern to parse and evaluate expressions like "3 + 5 * (2 - 8)".
// 2. Simple Query Language: A database application can implement a simple query language using the Interpreter pattern, allowing users to write queries like "SELECT * FROM users WHERE age > 30".
// 3. Configuration File Parser: An application that reads configuration files can use the Interpreter pattern to interpret the configuration syntax and apply settings accordingly.


// Consequences of using the Interpreter Design Pattern:
// 1. Flexibility: The Interpreter pattern provides a flexible way to define and interpret languages, making it easy to add new expressions or modify existing ones.
// 2. Reusability: The pattern promotes reusability of expression classes, as they can be combined to form more complex expressions.
// 3. Complexity: The Interpreter pattern can introduce complexity, especially for large or complex languages, as it may require a significant number of classes to represent the grammar.


// Components of the Interpreter Design Pattern:
// 1. Abstract Expression: Declares an abstract interpret operation that is common to all nodes in the abstract syntax tree.
// 2. Terminal Expression: Implements an interpret operation associated with terminal symbols in the grammar.
// 3. Non-Terminal Expression: Implements an interpret operation for non-terminal symbols in the grammar, typically by calling interpret on its child expressions.
// 4. Context: Contains information that is global to the interpreter, such as variable bindings or state information.
// 5. Client: Builds (or is given) an abstract syntax tree representing a particular sentence in the language and invokes the interpret operation.


using namespace std;

// ==========================================
// 1. Abstract Expression Interface
// ==========================================
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};


// ==========================================
// 2. Terminal Expression
// ==========================================
// Represents a raw number in the syntax tree
class NumberExpression : public Expression {
private:
    int number;
public:
    NumberExpression(int num) : number(num) {}
    
    int interpret() override {
        return number;
    }
};


// ==========================================
// 3. Non-Terminal Expressions
// ==========================================

// Represents an Addition operation (left + right)
class AddExpression : public Expression {
private:
    shared_ptr<Expression> leftOperand;
    shared_ptr<Expression> rightOperand;
public:
    AddExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : leftOperand(left), rightOperand(right) {}

    int interpret() override {
        return leftOperand->interpret() + rightOperand->interpret();
    }
};

// Represents a Subtraction operation (left - right)
class SubtractExpression : public Expression {
private:
    shared_ptr<Expression> leftOperand;
    shared_ptr<Expression> rightOperand;
public:
    SubtractExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : leftOperand(left), rightOperand(right) {}

    int interpret() override {
        return leftOperand->interpret() - rightOperand->interpret();
    }
};


class MultiplyExpression : public Expression {
private:
    shared_ptr<Expression> leftOperand;
    shared_ptr<Expression> rightOperand;
public:
    MultiplyExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : leftOperand(left), rightOperand(right) {}

    int interpret() override {
        return leftOperand->interpret() * rightOperand->interpret();
    }
};


// ==========================================
// Client Code
// ==========================================
int main() {
    // We want to evaluate the mathematical expression: (5 + 10) - 2
    
    // Step 1: Construct the leaf nodes (Terminal Expressions)
    auto num5 = make_shared<NumberExpression>(5);
    auto num10 = make_shared<NumberExpression>(10);
    auto num2 = make_shared<NumberExpression>(2);

    // Step 2: Build the Syntax Tree (Non-Terminal Expressions)
    // First, represent the addition: 5 + 10
    auto sum = make_shared<AddExpression>(num5, num10);
    auto product = make_shared<MultiplyExpression>(num5, num10); // Example of multiplication if needed

    // Next, represent the final subtraction: (5 + 10) - 2
    auto rootNode = make_shared<SubtractExpression>(sum, num2);

    // Step 3: Interpret the entire syntax tree recursively
    cout << "Evaluating expression tree for: (5 + 10) - 2" << endl;
    int result = rootNode->interpret();

    
    
    cout << "Result: " << result << endl; // Output will be 13

    cout << "\n--- Additional Example: Evaluating (5 * 10) - 2 ---" << endl;
    int result2 = product->interpret() - num2->interpret();
    cout << "Result: " << result2 << endl; // Output will be 48

    return 0;
}