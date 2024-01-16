#include "Includes.hpp"
#include "Interpreter.hpp"

int main() {
    string file_path = "example1.sunsh";
    Interpreter interpreter(file_path);
    interpreter.run();
}
