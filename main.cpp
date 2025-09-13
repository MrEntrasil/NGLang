#include "frontend/Lexer.hpp"
#include <fstream>
#include <memory>
#include <iostream>

int main(void) {
    std::ifstream file("index.mr");
    auto lexer = std::make_unique<NGLexer::Lexer>(file);
    auto tokens = lexer->tokenize();

    for (auto& t : *tokens) {
        std::cout << static_cast<int>(t.type) <<
        ' ' << t.text << '\n';
    }

    return EXIT_SUCCESS;
}