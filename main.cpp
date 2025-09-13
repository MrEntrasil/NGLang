#include "frontend/Lexer.hpp"
#include "frontend/Parser.hpp"
#include <fstream>
#include <memory>
#include <iostream>

int main(void) {
    std::ifstream file("index.mr");
    auto lexer = std::make_unique<NGLexer::Lexer>(file);
    auto tokens = lexer->tokenize();
    auto parser = std::make_unique<NGParser::Parser>(tokens);
    std::vector<std::unique_ptr<NGAst::Stmt>> program {};

    return EXIT_SUCCESS;
}