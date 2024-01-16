#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Includes.hpp"
#include "AbstractSyntaxTree.hpp"
#include "Parser.hpp"

class Interpreter {
private:
    unique_ptr<Program> root;
    string file_path;
public:
    Interpreter(string);
    void run();
};

#endif // !INTERPRETER_HPP