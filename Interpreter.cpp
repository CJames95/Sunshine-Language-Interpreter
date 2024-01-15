#include <iostream>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

class Token {
    public:
        enum class Symbol {
            // IDs and Integers
            Identifier, Integer,
            // Operators
            EQ,
            // Line End
            Semicolon,
            // Keywords
            IF, ELSE, PRINT,
            // Conditional Operator
            IS,
            // Punctuation
            Colon, DoubleQuote,
            // End of File
            EndOfFile,

        };

        Token() {}
        Token(Symbol symbol, string token) {
            t_symbol = symbol;
            t_token = token;
        }

        string toString() {
            return "Symbol: " + symbol() + ", Token: " + t_token;
        }

        string symbol() {
            switch (static_cast<int>(t_symbol)) {
                case 0:
                    return "Identifier";
                case 1:
                    return "Integer";
                case 2:
                    return "EQ";
                case 3:
                    return "Semicolon";
                case 4:
                    return "IF";
                case 5:
                    return "ELSE";
                case 6:
                    return "PRINT";
                case 7:
                    return "IS";
                case 8:
                    return "Colon";
                case 9:
                    return "DoubleQuote";
                case 10:
                    return "EndOfFile";
            }
        }

        int getSymbol() {
            return static_cast<int>(t_symbol);
        }

        string getToken() {
            return t_token;
        }
    private:
        Symbol t_symbol;
        string t_token;
};

class Lexer {
    private: 
        string source;
        size_t position = 0;

        Token identifier() {
            map<std::string, Token::Symbol> keyword_map = {
                {"if", Token::Symbol::IF},
                {"else", Token::Symbol::ELSE},
                {"is", Token::Symbol::IS},
                {"print", Token::Symbol::PRINT},
                {"equals", Token::Symbol::EQ}
            };
            char current = source[position];
            size_t startPosition = position;
            while (is_identifier(current)) {
                current = source[position];
                if (is_identifier(source[position])) {
                    position++;
                }
            }
            string token_string = source.substr(startPosition, position - startPosition);
            auto iterator = keyword_map.find(token_string);
            if (iterator != keyword_map.end()) {
                return Token(iterator->second, token_string);
            }
            else {
                return Token(Token::Symbol::Identifier, token_string);
            }
        }
        Token integer() {
            char current = source[position];
            size_t startPosition = position;
            while (is_digit(current)) {
                current = source[position];
                if (is_digit(source[position])) {
                    position++;
                }
            }
            return Token(Token::Symbol::Integer, source.substr(startPosition, position - startPosition));
        }
        bool is_space(char current) {
            switch (current) {
            case ' ':
                return true;
            default:
                return false;
            }
        }
        bool is_digit(char current) {
            switch (current) {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '0':
                    return true;
                default:
                    return false;

            }
        }
        bool is_identifier(char current) {
            switch (current) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '_':
                    return true;
                default:
                    return false;
            }
        }

    public:
        Lexer(const string& file_path) {
            ifstream file(file_path);
            if (file) {
                source.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            }
            file.close();
        }

        vector<Token> tokenize() {
            vector<Token> tokens;
            while (position < source.length()) {
                char current_char = source[position];
                switch (current_char) {
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                    case 'g':
                    case 'h':
                    case 'i':
                    case 'j':
                    case 'k':
                    case 'l':
                    case 'm':
                    case 'n':
                    case 'o':
                    case 'p':
                    case 'q':
                    case 'r':
                    case 's':
                    case 't':
                    case 'u':
                    case 'v':
                    case 'w':
                    case 'x':
                    case 'y':
                    case 'z':
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'J':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'O':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'U':
                    case 'V':
                    case 'W':
                    case 'X':
                    case 'Y':
                    case 'Z':
                        tokens.push_back(identifier());
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        tokens.push_back(integer());
                        break;
                    case ';':
                        tokens.push_back(Token(Token::Symbol::Semicolon, string(1, current_char)));
                        position++;
                        break;
                    case '\"':
                        tokens.push_back(Token(Token::Symbol::DoubleQuote, string(1, current_char)));
                        position++;
                        break;
                    case ':':
                        tokens.push_back(Token(Token::Symbol::Colon, string(1, current_char)));
                        position++;
                        break;
                    case ' ':
                    case '\t':
                    case '\r':
                    case '\n':
                        position++;
                        break;
                }
            }
            tokens.push_back(Token(Token::Symbol::EndOfFile, ""));
            return tokens;
        }
};

class Identifier;
class Integer;
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
    virtual ~Expression() = default;
    virtual void accept(Visitor& visitor) = 0;
    virtual string toString() const {
        return "undefined expression";
    }
};

class Identifier : public Expression {
private:
    string id;

public:
    Identifier() {}
    Identifier(string new_id)
        : id(new_id) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    string getID() {
        return id;
    }

    string toString() const override {
        return "(id " + id + ")";
    }
};

class Integer : public Expression {
private:
    int integer;

public:
    Integer() {}
    Integer(int new_integer)
        : integer(new_integer) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    int getInteger() {
        return integer;
    }

    string toString() const override {
        return "(integer " + to_string(integer) + ")";
    }
};

class Unary : public Expression {
private:
    string unary_operator;
    Expression* expression_1;

public:
    Unary() {}
    Unary(string new_unary_operator, Expression* new_expression_1)
        : unary_operator(new_unary_operator), expression_1(new_expression_1) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    string toString() const override {
        return "(" + unary_operator + " " + expression_1->toString() + ")";
    }

};

class Binary : public Expression {
private:
    string binary_operator;
    Expression* expression_1;
    Expression* expression_2;

public:
    Binary() {}
    Binary(string new_binary_operator, Expression* new_expression_1, Expression* new_expression_2)
        : binary_operator(new_binary_operator), expression_1(new_expression_1), expression_2(new_expression_2) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    string getBinaryOperator() {
        return binary_operator;
    }

    Expression* getExpression1() {
        return expression_1;
    }

    Expression* getExpression2() {
        return expression_2;
    }

    string toString() const override {
        return "(" + binary_operator + " " + expression_1->toString() + " " + expression_2->toString() + ")";
    }

};

class Program {
    // Base class for all future nodes
    public:
        ~Program() = default;
        virtual void accept(Visitor& visitor) = 0;
};

class Statement : public Program {
    private:
        unique_ptr<Statement> statement_1;
        unique_ptr<Statement> statement_2;

    public:
        Statement() {}
        Statement(unique_ptr<Statement> state_1, unique_ptr<Statement> state_2) 
            : statement_1(move(state_1)), statement_2(move(state_2)) {}

        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        Statement* getStatement1() {
            return statement_1.get();
        }

        Statement* getStatement2() {
            return statement_2.get();
        }

        virtual string toString() {
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
};

class Assignment : public Statement {
    private:
        Identifier left_hand_side;
        Expression* right_hand_side;
    public:
        Assignment() {}
        Assignment(Identifier new_left_hand_side, Expression* new_right_hand_side)  
            : left_hand_side(new_left_hand_side), right_hand_side(new_right_hand_side) {}

        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        Identifier getLeftHandSide() {
            return left_hand_side;
        }

        Expression* getRightHandSide() {
            return right_hand_side;
        }

        string toString() override {
            return "(= " + left_hand_side.toString() + " " + right_hand_side->toString() + ")";
        }
};

class IfStatement : public Statement {
    private:
        Expression* test;
        unique_ptr<Statement> then_statement;
        unique_ptr<Statement> else_statement;

    public:
        IfStatement() {}
        IfStatement(Expression* new_test, unique_ptr<Statement> new_then_statement)
            : test(new_test), then_statement(move(new_then_statement)) {}
        IfStatement(Expression* new_test, unique_ptr<Statement> new_then_statement, unique_ptr<Statement> new_else_statement)
            : test(new_test), then_statement(move(new_then_statement)), else_statement(move(new_else_statement)) {}

        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        Expression* getTest() {
            return test;
        }

        unique_ptr<Statement> getThenStatement() {
            return move(then_statement);
        }

        unique_ptr<Statement> getElseStatement() {
            return move(else_statement);
        }

        string toString() override {
            if (else_statement == nullptr) {
                return "(if " + test->toString() + " " + then_statement->toString() + ")";
            }
            else {
                return "(if " + test->toString() + " " + then_statement->toString() + else_statement->toString() + ")";
            }
        }
};

class PrintStatement : public Statement {
    private: 
        Expression* expression;

    public:
        PrintStatement() {}
        PrintStatement(Expression* new_expression) 
            : expression(new_expression) {}

        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        Expression* getExpression() {
            return expression;
        }

        string toString() override {
            return "(print " + expression->toString() + ")";
        }
};

class ExecutionVisitor : public Visitor {
    private:
        unordered_map<string, int> symbolTable;
        int last_evaluated_value;
        //string last_evaluated_identifier;
    public:
        ExecutionVisitor() {}

        void visit(Identifier& node) override {
            string id_name = node.getID();
            if (symbolTable.find(id_name) != symbolTable.end()) {
                last_evaluated_value = symbolTable[id_name];
            }
            else {
                throw runtime_error("Unidenfied Variable: " + id_name);
            }
        }
        void visit(Integer& node) override {
            last_evaluated_value = node.getInteger();
        }
        void visit(Unary& node) override {
            // unused
        }
        void visit(Binary& node) override {
            int left_hand_value;
            int right_hand_value;
            if (node.getBinaryOperator().compare("is") == 0) {
                node.getExpression1()->accept(*this);
                left_hand_value = last_evaluated_value;
                node.getExpression2()->accept(*this);
                right_hand_value = last_evaluated_value;
                if (left_hand_value == right_hand_value) {
                    last_evaluated_value = 1;
                }
                else {
                    last_evaluated_value = 0;
                }
            }
        }
        void visit(Statement& node) override {
            if (node.getStatement1() != nullptr) {
                node.getStatement1()->accept(*this);
            }
            if (node.getStatement2() != nullptr) {
                node.getStatement2()->accept(*this);
            }

        }
        void visit(Assignment& node) override {
            node.getRightHandSide()->accept(*this); // Evaluate the Integer
            int value = last_evaluated_value;

            // Assign the value variable to the unordered_map so that the identifier and the value are together.
            symbolTable[node.getLeftHandSide().getID()] = value;

        }
        void visit(IfStatement& node) override {
            node.getTest()->accept(*this);
            int condition_value = last_evaluated_value;

            if (condition_value != 0) {
                node.getThenStatement()->accept(*this);
            }
            else if (node.getElseStatement() != nullptr) {
                node.getElseStatement()->accept(*this);
            }
        }
        void visit(PrintStatement& node) override {
            node.getExpression()->accept(*this);
            cout << last_evaluated_value << endl;
        }
};

class Parser {
    private:
        vector<Token> p_tokens;
        vector<Token>::iterator p_position;
        Token p_token;
        bool eof_flag;

        void nextToken() {
            if (p_token.symbol().compare("EndOfFile") != 0) {
                p_position++;
                p_token = *p_position;
            }
            else {
                eof_flag = true;
            }
        }
    public:
        Parser(string file_path) {
            Lexer lexer(file_path);
            p_tokens = lexer.tokenize();
            p_position = p_tokens.begin();
            p_token = *p_position;
            eof_flag = false;
        }

        unique_ptr<Statement> program() {
            unique_ptr<Statement> statement;
            while(eof_flag != true) {
                statement = suite();
                nextToken();
            }
            return move(statement);
        } 

        unique_ptr<Statement> suite() {
            auto statement_1 = statement();
            while(p_token.symbol().compare("Identifier") == 0 ||
                  p_token.symbol().compare("IF") == 0 ||
                  p_token.symbol().compare("PRINT") == 0) {
                auto statement_2 = statement();
                statement_1 = make_unique<Statement>(move(statement_1), move(statement_2));
            }
            return statement_1;
        }

        unique_ptr<Statement> statement() {
            unique_ptr<Statement> statement_1;

            switch (p_token.getSymbol()) {
                case 0: { // Identifier
                    if (p_token.getToken().compare("declare") != 0) {
                        // error: declare missing
                    }
                    nextToken();
                    if (p_token.getToken().compare("variable") != 0) {
                        // error: variable missing
                    }
                    nextToken();
                    if (p_token.getToken().compare("named") != 0) {
                        // error: named missing
                    }
                    nextToken();
                    Identifier new_id_1(p_token.getToken());
                    nextToken();
                    if (p_token.getToken().compare("equals") != 0) {
                        // error: equals missing
                    }
                    nextToken();
                    Expression* new_expression = new Integer(stoi(p_token.getToken()));
                    nextToken();
                    if (p_token.getToken().compare(";") != 0) {
                        // error: semicolon missing
                    }
                    statement_1 = make_unique<Assignment>(new_id_1, new_expression);
                    nextToken();
                    break;
                }
                case 4: { // IF
                    nextToken();
                    Expression* new_id_2 = new Identifier(p_token.getToken());
                    nextToken();
                    if (p_token.getToken().compare("is") != 0) {
                        // error: is missing
                    }
                    string new_operator = p_token.getToken();
                    nextToken();
                    Expression* new_integer_1 = new Integer(stoi(p_token.getToken()));
                    Binary* new_binary_1 = new Binary(new_operator, new_id_2, new_integer_1);
                    nextToken();
                    if (p_token.getToken().compare(":") != 0) {
                        // error: colon missing
                    }
                    nextToken();
                    auto statement_2 = suite();
                    if (p_token.getToken().compare("else") != 0) {
                        statement_1 = make_unique<IfStatement>(new_binary_1, move(statement_2));
                        break;
                    }
                    else {
                        nextToken();
                        if (p_token.getToken().compare(":") != 0) {
                            //error: colon missing
                        }
                        nextToken();
                        auto statement_3 = suite();
                        statement_1 = make_unique<IfStatement>(new_binary_1, move(statement_2), move(statement_3));
                        break;
                    }
                }
                case 6: { // PRINT
                    nextToken();
                    statement_1 = make_unique<PrintStatement>(new Integer(stoi(p_token.getToken())));
                    nextToken();
                    if (p_token.getToken().compare(";") != 0) {
                        // error: semicolon missing
                    }
                    nextToken();
                    break;
                }
            }
            return statement_1;
        }
};

class Interpreter {
    private: 
        unique_ptr<Program> root;
        string file_path;
    public:
        Interpreter(string file_path) : file_path(file_path) {
            Parser parser(file_path);
            root = parser.program();
        }

        void run() {
            if (!root) {
                throw runtime_error("No program to run. Root node is null.");
            }
            ExecutionVisitor visitor;
            root->accept(visitor);
        }
};

int main() {
    string file_path = "example1.sunsh";
    Interpreter interpreter(file_path);
    interpreter.run();
}