# Sunshine Language Interpreter
 This is an interpreter for a small scripting language named Sunshine. It uses '.sunsh' file types. The scripting language uses primarily plain text to do everything so that it reads as close to english as is possible without adhering to thousands of possible edge cases.

## EBNF
This is a rough EBNF for the Sunshine programming language currently.
```
<if_statement> ::= <if_declaration> <block> (<else_declaration> <block>)?
<if_declaration> ::= "if " <identifier> " is " <digit> ":" "\n"?
<else_declaration> ::= "else:" "\n"?
<block> ::= <statements>
<statements> ::= <statement>+
<statement> ::= <simple_statement> | <compound_statement>
<simple_statement> ::= <assignment> | <print>
<compound_statement> ::= <if_statement>
<print> ::= "print " (<identifier> | <string> | <digit>*) <line_termination>
<assignment> ::= <declaration_keywords> <identifier> <assignment_operator> (<string> | <digit>*) <line_termination> "\n"?
<declaration_keywords> ::= "declare a variable named "
<assignment_operator> ::= " that equals "
<string> ::= "\"" ([a-z] | [A-Z] | " ")* "\""
<line_termination> ::= ";"
<identifier> ::= <nondigit> (<nondigit> | <digit>)*
<nondigit> ::= ([a-z] | [A-Z] | "_")
<digit> ::= [0-9]
```
