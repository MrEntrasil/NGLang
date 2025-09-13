#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <memory>

namespace NGLexer {
    enum class TokenType {
        IDENT, STRING, NUMBER,
        KEYWORD, BINARY,
        LPAREN, RPAREN
    };
    struct Token {
        std::string text;
        TokenType type;
    };
    using Tokens = std::vector<Token>;
    class Lexer {
    private:
        size_t pos;
        std::istream& is;
    public:
        Lexer(std::istream& file) : is(file), pos(0) {}
        std::unique_ptr<Tokens> tokenize();
    };
}