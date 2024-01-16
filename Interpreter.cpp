#include "Interpreter.hpp"

Interpreter::Interpreter(string file_path) 
    : file_path(file_path) {
    Parser parser(file_path);
    //unique_ptr<Statement> temp_root;
    //temp_root = parser.program();
    root = parser.program();
    //cout << temp_root->toString() << endl;
}

void Interpreter::run() {
    if (!root) {
        throw runtime_error("No program to run. Root node is null.");
    }
    ExecutionVisitor visitor;
    root->accept(visitor);
}