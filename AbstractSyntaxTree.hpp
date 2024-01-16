#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include "Includes.hpp"

class Identifier;
class Integer;
class String;
class Unary;
class Binary;
class Statement;
class Assignment;
class IfStatement;
class PrintStatement;

class Visitor {
    // Base calass for my visitor objects
public:
    virtual void visit(Identifier& node) = 0;
    virtual void visit(Integer& node) = 0;
    virtual void visit(String& node) = 0;
    virtual void visit(Unary& node) = 0;
    virtual void visit(Binary& node) = 0;
    virtual void visit(Statement& node) = 0;
    virtual void visit(Assignment& node) = 0;
    virtual void visit(IfStatement& node) = 0;
    virtual void visit(PrintStatement& node) = 0;
};

class Expression {
    // Base class for storing data types.
public:
    virtual ~Expression();
    virtual void accept(Visitor& visitor) = 0;
    virtual string toString() const;
};

class Identifier : public Expression {
private:
    string id;
public:
    Identifier();
    Identifier(string);
    void accept(Visitor&) override;
    string getID();
    string toString() const override;
};

class Integer : public Expression {
private:
    int integer;
public:
    Integer();
    Integer(int);
    void accept(Visitor&) override;
    int getInteger();
    string toString() const override;
};

class String : public Expression {
private:
    string string_variable;
public:
    String();
    String(string);
    void accept(Visitor&) override;
    string getString();
    string toString() const override;
};

class Unary : public Expression {
private:
    string unary_operator;
    Expression* expression_1;
public:
    Unary();
    Unary(string, Expression*);
    void accept(Visitor&) override;
    string toString() const override;
};

class Binary : public Expression {
private:
    string binary_operator;
    Expression* expression_1;
    Expression* expression_2;

public:
    Binary();
    Binary(string, Expression*, Expression*);
    void accept(Visitor&) override;
    string getBinaryOperator();
    Expression* getExpression1();
    Expression* getExpression2();
    string toString() const override;
};

class Program {
    // Base class for all future nodes
public:
    virtual ~Program();
    virtual void accept(Visitor& visitor) = 0;
};

class Statement : public Program {
private:
    unique_ptr<Statement> statement_1;
    unique_ptr<Statement> statement_2;

public:
    Statement();
    Statement(unique_ptr<Statement>, unique_ptr<Statement>);
    void accept(Visitor&) override;
    Statement* getStatement1();
    Statement* getStatement2();
    virtual string toString();
};

class Assignment : public Statement {
private:
    Identifier left_hand_side;
    Expression* right_hand_side;
public:
    Assignment();
    Assignment(Identifier, Expression*);
    void accept(Visitor&) override;
    Identifier getLeftHandSide();
    Expression* getRightHandSide();
    string toString() override;
};

class IfStatement : public Statement {
private:
    Expression* test;
    unique_ptr<Statement> then_statement;
    unique_ptr<Statement> else_statement;
public:
    IfStatement();
    IfStatement(Expression*, unique_ptr<Statement>);
    IfStatement(Expression*, unique_ptr<Statement>, unique_ptr<Statement>);
    void accept(Visitor&) override;
    Expression* getTest();
    unique_ptr<Statement> getThenStatement();
    unique_ptr<Statement> getElseStatement();
    string toString() override;
};

class PrintStatement : public Statement {
private:
    Expression* expression;
public:
    PrintStatement();
    PrintStatement(Expression*);
    void accept(Visitor&) override;
    Expression* getExpression();
    string toString() override;
};

class ExecutionVisitor : public Visitor {
private:
    unordered_map<string, variant<int, string>> symbolTable;
    variant<int, string> last_evaluated_value;
public:
    ExecutionVisitor();
    void visit(Identifier& node) override;
    void visit(Integer& node) override;
    void visit(String& node) override;
    void visit(Unary& node) override;
    void visit(Binary& node) override;
    void visit(Statement& node) override;
    void visit(Assignment& node) override;
    void visit(IfStatement& node) override;
    void visit(PrintStatement& node) override;
};

#endif // !ABSTRACTSYNTAXTREE_HPP