#include "Lexer.hpp"
#include <iostream>

std::unique_ptr<NGLexer::Tokens> NGLexer::Lexer::tokenize() {
    auto tokens = std::make_unique<Tokens>();
    char c;
    int n;
    std::string buff {};

    while ((n = is.get()) != EOF) {
        c = static_cast<char>(n);
        if (std::isspace(c)) {
            continue;
        }
        else if (std::isdigit(c)) {
            buff.push_back(c);
            while ((n = is.peek()) != EOF && std::isdigit(n)) {
                c = static_cast<char>(is.get());
                buff.push_back(c);
            }
            tokens->push_back({ buff, NGLexer::TokenType::NUMBER });
            
            buff.clear();
            continue;
        }
        else if (std::isalpha(c)) {
            buff.push_back(c);
            while ((n = is.peek()) != EOF && std::isalnum(n)) {
                c = static_cast<char>(is.get());
                buff.push_back(c);
            }
            if (buff == "fun") tokens->push_back({ buff, NGLexer::TokenType::KEYWORD });
            else tokens->push_back({ buff, NGLexer::TokenType::IDENT });
            
            buff.clear();
            continue;
        }
        else if (c == '"') {
            while ((n = is.peek()) != EOF) {
                c = static_cast<char>(is.get());
                if (c == '"') break;
                buff.push_back(c);
            }
            tokens->push_back({ buff, NGLexer::TokenType::STRING });

            buff.clear();
            continue;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            tokens->push_back({ std::string {c}, NGLexer::TokenType::BINARY });
            continue;
        }
        else if (c == '(') {
            tokens->push_back({ "(", NGLexer::TokenType::LPAREN });
            continue;
        }
        else if (c == ')') {
            tokens->push_back({ ")", NGLexer::TokenType::RPAREN });
            continue;
        }
        else if (c == ';') {
            tokens->push_back({ ";", NGLexer::TokenType::SEMICOLON });
            continue;
        }
        else if (c == ',') {
            tokens->push_back({ ",", NGLexer::TokenType::COLON });
            continue;
        }
        else throw std::runtime_error("Unexpected token: "+std::string {c});
    }
    return tokens;
}