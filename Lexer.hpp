#ifndef LEXER_HPP
#define LEXER_HPP

#include "Includes.hpp"
#include "Token.hpp"

class Lexer {
private:
    string source;
    size_t position = 0;
    
    Token identifier();
    Token integer();
    bool is_space(char);
    bool is_digit(char);
    bool is_identifier(char);
public:
    Lexer(const string&);
    vector<Token> tokenize();
};

#endif // !LEXER_HPP