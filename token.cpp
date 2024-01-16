#include "Token.hpp"

Token::Token() {}
Token::Token(Symbol symbol, string token) {
    t_symbol = symbol;
    t_token = token;
}
string Token::toString() {
    return "Symbol: " + symbol() + ", Token: " + t_token;
}
string Token::symbol() {
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
int Token::getSymbol() {
    return static_cast<int>(t_symbol);
}
string Token::getToken() {
    return t_token;
}