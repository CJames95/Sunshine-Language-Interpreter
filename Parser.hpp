#ifndef PARSER_HPP
#define PARSER_HPP


#include "Includes.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "AbstractSyntaxTree.hpp"

class Parser {
private:
    vector<Token> p_tokens;
    vector<Token>::iterator p_position;
    Token p_token;
    bool eof_flag;

    void nextToken();
public:
    Parser(string);
    unique_ptr<Statement> program();
    unique_ptr<Statement> suite();
    unique_ptr<Statement> statement();
    Expression* handleString();
};

#endif // !PARSER_HPP