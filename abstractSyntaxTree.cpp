#include "AbstractSyntaxTree.hpp"

// Expression Class Object Function Declarations
Expression::~Expression() = default;
string Expression::toString() const {
    return "undefined expression";
}

// Identifier Class Object Function Declarations
Identifier::Identifier() {}
Identifier::Identifier(string new_id)
    : id(new_id) {}
void Identifier::accept(Visitor& visitor) {
    visitor.visit(*this);
}
string Identifier::getID() {
    return id;
}
string Identifier::toString() const {
    return "(id " + id + ")";
}

// Integer Class Object Function Declarations
Integer::Integer() {}
Integer::Integer(int new_integer)
    : integer(new_integer) {}
void Integer::accept(Visitor& visitor) {
    visitor.visit(*this);
}
int Integer::getInteger() {
    return integer;
}
string Integer::toString() const {
    return "(integer " + to_string(integer) + ")";
}

// String Class Object Function Declarations
String::String() {}
String::String(string new_string)
    : string_variable(new_string) {}
void String::accept(Visitor& visitor) {
    visitor.visit(*this);
}
string String::getString() {
    return string_variable;
}
string String::toString() const {
    return "(string (" + string_variable + "))";
}

// Unary Class Object Function Declarations
Unary::Unary() {}
Unary::Unary(string new_unary_operator, Expression* new_expression_1)
    : unary_operator(new_unary_operator), expression_1(new_expression_1) {}
void Unary::accept(Visitor& visitor) {
    visitor.visit(*this);
}
string Unary::toString() const {
    return "(" + unary_operator + " " + expression_1->toString() + ")";
}

// Binary Class Object Function Declarations
Binary::Binary() {}
Binary::Binary(string new_binary_operator, Expression* new_expression_1, Expression* new_expression_2)
    : binary_operator(new_binary_operator), expression_1(new_expression_1), expression_2(new_expression_2) {}
void Binary::accept(Visitor& visitor) {
    visitor.visit(*this);
}
string Binary::getBinaryOperator() {
    return binary_operator;
}
Expression* Binary::getExpression1() {
    return expression_1;
}
Expression* Binary::getExpression2() {
    return expression_2;
}
string Binary::toString() const {
    return "(" + binary_operator + " " + expression_1->toString() + " " + expression_2->toString() + ")";
}

// Program Class Object Function Declarations
Program::~Program() = default;

// Statement Class Object Function Declarations
Statement::Statement() {}
Statement::Statement(unique_ptr<Statement> state_1, unique_ptr<Statement> state_2)
    : statement_1(move(state_1)), statement_2(move(state_2)) {}
void Statement::accept(Visitor& visitor) {
    visitor.visit(*this);
}
Statement* Statement::getStatement1() {
    return statement_1.get();
}
Statement* Statement::getStatement2() {
    return statement_2.get();
}
string Statement::toString() {
    if (statement_1 == nullptr) {
        return "()";
    }
    else {
        if (statement_2 == nullptr) {
            return "(" + statement_1->toString() + ")";
        }
        else {
            return "(" + statement_1->toString() + " " + statement_2->toString() + ")";
        }
    }
}

// Assignment Class Object Function Declarations
Assignment::Assignment() {}
Assignment::Assignment(Identifier new_left_hand_side, Expression* new_right_hand_side)
    : left_hand_side(new_left_hand_side), right_hand_side(new_right_hand_side) {}
void Assignment::accept(Visitor& visitor) {
    visitor.visit(*this);
}
Identifier Assignment::getLeftHandSide() {
    return left_hand_side;
}
Expression* Assignment::getRightHandSide() {
    return right_hand_side;
}
string Assignment::toString() {
    return "(= " + left_hand_side.toString() + " " + right_hand_side->toString() + ")";
}

// IfStatement Class Object Function Declarations
IfStatement::IfStatement() {}
IfStatement::IfStatement(Expression* new_test, unique_ptr<Statement> new_then_statement)
    : test(new_test), then_statement(move(new_then_statement)) {}
IfStatement::IfStatement(Expression* new_test, unique_ptr<Statement> new_then_statement, unique_ptr<Statement> new_else_statement)
    : test(new_test), then_statement(move(new_then_statement)), else_statement(move(new_else_statement)) {}
void IfStatement::accept(Visitor& visitor) {
    visitor.visit(*this);
}
Expression* IfStatement::getTest() {
    return test;
}
unique_ptr<Statement> IfStatement::getThenStatement() {
    return move(then_statement);
}
unique_ptr<Statement> IfStatement::getElseStatement() {
    return move(else_statement);
}
string IfStatement::toString() {
    if (else_statement == nullptr) {
        return "(if " + test->toString() + " " + then_statement->toString() + ")";
    }
    else {
        return "(if " + test->toString() + " " + then_statement->toString() + else_statement->toString() + ")";
    }
}

// Print Class Object Function Declarations
PrintStatement::PrintStatement() {}
PrintStatement::PrintStatement(Expression* new_expression)
    : expression(new_expression) {}
void PrintStatement::accept(Visitor& visitor) {
    visitor.visit(*this);
}
Expression* PrintStatement::getExpression() {
    return expression;
}
string PrintStatement::toString() {
    return "(print " + expression->toString() + ")";
}

// ExecutionVisitor Class Object Function Declarations
ExecutionVisitor::ExecutionVisitor() {}
void ExecutionVisitor::visit(Identifier& node) {
    string id_name = node.getID();
    if (symbolTable.find(id_name) != symbolTable.end()) {
        last_evaluated_value = symbolTable[id_name];
    }
    else {
        throw runtime_error("Unidenfied Variable: " + id_name);
    }
}
void ExecutionVisitor::visit(Integer& node) {
    last_evaluated_value = node.getInteger();
}
void ExecutionVisitor::visit(String& node) {
    // unused
}
void ExecutionVisitor::visit(Unary& node) {
    // unused
}
void ExecutionVisitor::visit(Binary& node) {
    int left_hand_value;
    int right_hand_value;
    if (node.getBinaryOperator().compare("is") == 0) {
        node.getExpression1()->accept(*this);
        left_hand_value = get<int>(last_evaluated_value);
        node.getExpression2()->accept(*this);
        right_hand_value = get<int>(last_evaluated_value);
        if (left_hand_value == right_hand_value) {
            last_evaluated_value = 1;
        }
        else {
            last_evaluated_value = 0;
        }
    }
}
void ExecutionVisitor::visit(Statement& node) {
    if (node.getStatement1() != nullptr) {
        node.getStatement1()->accept(*this);
    }
    if (node.getStatement2() != nullptr) {
        node.getStatement2()->accept(*this);
    }

}
void ExecutionVisitor::visit(Assignment& node) {
    node.getRightHandSide()->accept(*this); // Evaluate the Integer
    variant<int, string> value = last_evaluated_value;

    // Assign the value variable to the unordered_map so that the identifier and the value are together.
    symbolTable[node.getLeftHandSide().getID()] = value;

}
void ExecutionVisitor::visit(IfStatement& node) {
    node.getTest()->accept(*this);
    int condition_value = get<int>(last_evaluated_value);

    if (condition_value != 0) {
        node.getThenStatement()->accept(*this);
    }
    else if (node.getElseStatement() != nullptr) {
        node.getElseStatement()->accept(*this);
    }
}
void ExecutionVisitor::visit(PrintStatement& node) {
    node.getExpression()->accept(*this);

    std::visit([](const auto& print_value) {
        cout << print_value << endl;
        }, last_evaluated_value);
}