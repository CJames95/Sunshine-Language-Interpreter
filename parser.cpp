#include "Parser.hpp"

void Parser::nextToken() {
    if (p_token.symbol().compare("EndOfFile") != 0) {
        p_position++;
        p_token = *p_position;
    }
    else {
        eof_flag = true;
    }
}

Parser::Parser(string file_path) {
    Lexer lexer(file_path);
    p_tokens = lexer.tokenize();
    p_position = p_tokens.begin();
    p_token = *p_position;
    eof_flag = false;
}

unique_ptr<Statement> Parser::program() {
    unique_ptr<Statement> statement;
    while (eof_flag != true) {
        statement = suite();
        nextToken();
    }
    return move(statement);
}

unique_ptr<Statement> Parser::suite() {
    auto statement_1 = statement();
    while (p_token.symbol().compare("Identifier") == 0 ||
        p_token.symbol().compare("IF") == 0 ||
        p_token.symbol().compare("PRINT") == 0) {
        auto statement_2 = statement();
        statement_1 = make_unique<Statement>(move(statement_1), move(statement_2));
    }
    return statement_1;
}

unique_ptr<Statement> Parser::statement() {
    unique_ptr<Statement> statement_1;
    Expression* new_expression = nullptr;

    switch (p_token.getSymbol()) {
    case 0: { // Identifier
        if (p_token.getToken().compare("declare") != 0) {
            // error: declare missing'
            cout << "Error: 'declare' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        if (p_token.getToken().compare("a") != 0) {
            // error: a missing
            cout << "Error: 'a' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        if (p_token.getToken().compare("variable") != 0) {
            // error: variable missing
            cout << "Error: 'variable' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        if (p_token.getToken().compare("named") != 0) {
            // error: named missing
            cout << "Error: 'named' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        Identifier new_id_1(p_token.getToken());
        nextToken();
        if (p_token.getToken().compare("that") != 0) {
            // error: that missing
            cout << "Error: 'that' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        if (p_token.getToken().compare("equals") != 0) {
            // error: equals missing
            cout << "Error: 'equals' keyword missing." << endl;
            //exit(0);
        }
        else {
            nextToken();
        }
        if (p_token.symbol().compare("DoubleQuote") == 0) {
            new_expression = handleString();
        }
        else if (p_token.symbol().compare("Integer") == 0) {
            new_expression = new Integer(stoi(p_token.getToken()));
        }
        nextToken();
        if (p_token.getToken().compare(";") != 0) {
            // error: semicolon missing
            throw runtime_error("Error: ';' missing at end of line.");
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

Expression* Parser::handleString() {
    nextToken();
    string concat_string = p_token.getToken();
    nextToken();
    while (p_token.symbol().compare("DoubleQuote") != 0) {
        concat_string = concat_string + " " + p_token.getToken();
        nextToken();
    }
    Expression* string_1 = new String(concat_string);
    return string_1;
}