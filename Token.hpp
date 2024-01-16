#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Includes.hpp"

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
    Token();
    Token(Symbol, string);
    string toString();
    string symbol();
    int getSymbol();
    string getToken();
private:
    Symbol t_symbol;
    string t_token;
};

#endif // !TOKEN_HPP