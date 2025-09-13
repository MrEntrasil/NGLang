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

std::unique_ptr<NGAst::Stmt> NGParser::Parser::parse_stmt() {
    NGLexer::Token token = tokens->at(pos);
    if (token.type == NGLexer::TokenType::KEYWORD || token.text == "print") {
        return parsePrint_stmt();
    }
    else if (token.type == NGLexer::TokenType::IDENT || token.text == "decl") {
        return parseVarDecl_stmt();
    } else return parseExprStmt();
}

std::unique_ptr<NGAst::Stmt> NGParser::Parser::parsePrint_stmt() {
    get();
    auto expr = parse_expr();
    expect(NGLexer::TokenType::SEMICOLON);
    return std::make_unique<NGAst::PrintStmt>(std::move(expr));
}

std::unique_ptr<NGAst::Stmt> NGParser::Parser::parseVarDecl_stmt() {
    NGLexer::Token token = tokens->at(pos);
    token = get();
    if (token.type != NGLexer::TokenType::IDENT) throw std::runtime_error("Identifier expected after: "+token.text);
    get();
    expect(NGLexer::TokenType::COLON);
    auto init = parse_expr();
    expect(NGLexer::TokenType::SEMICOLON);
    return std::make_unique<NGAst::VarDeclStmt>(token.text, std::move(init));
}

std::unique_ptr<NGAst::Stmt> NGParser::Parser::parseExprStmt() {
    auto expr = parse_expr();
    expect(NGLexer::TokenType::SEMICOLON);
    return std::make_unique<NGAst::ExprStmt>(std::move(expr));
}

void NGParser::Parser::expect(NGLexer::TokenType type) {
    NGLexer::Token token = tokens->at(pos);
    if (token.type != type) throw std::runtime_error("Unexpected token: "+token.text);
    get();
}