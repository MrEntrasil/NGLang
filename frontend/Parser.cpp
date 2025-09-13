#include "Parser.hpp"

std::unique_ptr<NGAst::Expr> NGParser::Parser::parse_expr() {
    NGLexer::Token token = tokens->at(pos);
    auto left = parseTerm_expr();
    while (token.text == "+" || token.text == "-") {
        char op = (token.text == "+") ? '+' : '-';
        token = get();
        auto right = parseTerm_expr();
        left = std::make_unique<NGAst::BinaryExpr>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<NGAst::Expr> NGParser::Parser::parseTerm_expr() {
    NGLexer::Token token = tokens->at(pos);
    auto left = parseFactor_expr();
    while (token.text == "*" || token.text == "/") {
        char op = (token.text == "*") ? '*' : '/';
        token = get();
        auto right = parseFactor_expr();
        left = std::make_unique<NGAst::BinaryExpr>(op, left, right);
    }
    return left;
}

std::unique_ptr<NGAst::Expr> NGParser::Parser::parseFactor_expr() {
    NGLexer::Token token = tokens->at(pos);
    if (token.type == NGLexer::TokenType::NUMBER) {
        std::string value = token.text;
        token = get();
        return std::make_unique<NGAst::LiteralExpr>(value, NGLexer::TokenType::NUMBER);
    }
    else if (token.type == NGLexer::TokenType::LPAREN) {
        token = get();
        auto expr = parse_expr();
        if (token.type != NGLexer::TokenType::RPAREN) throw std::runtime_error("Expected ')' after '(");
        token = get();
        return expr;
    } else throw std::runtime_error("Invalid factor: "+token.text);
}