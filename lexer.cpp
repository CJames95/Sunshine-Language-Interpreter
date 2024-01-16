#include "Lexer.hpp"

Token Lexer::identifier() {
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
Token Lexer::integer() {
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
bool Lexer::is_space(char current) {
    switch (current) {
    case ' ':
        return true;
    default:
        return false;
    }
}
bool Lexer::is_digit(char current) {
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
bool Lexer::is_identifier(char current) {
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
Lexer::Lexer(const string& file_path) {
    ifstream file(file_path);
    if (file) {
        source.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    }
    file.close();
}

vector<Token> Lexer::tokenize() {
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