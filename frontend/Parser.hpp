#pragma once
#include <memory>
#include "Lexer.hpp"
#include "Ast.hpp"

namespace NGParser {
    class Parser {
    private:
        std::unique_ptr<NGLexer::Tokens> tokens;
        size_t pos;
        NGLexer::Token get();
        std::unique_ptr<NGAst::Stmt> parseVarDecl_stmt();
        std::unique_ptr<NGAst::Stmt> parsePrint_stmt();
        std::unique_ptr<NGAst::Expr> parseTerm_expr();
        std::unique_ptr<NGAst::Expr> parseFactor_expr();
    public:
        Parser(std::unique_ptr<NGLexer::Tokens> tk) : tokens(std::move(tk)), pos(0) {}
        std::unique_ptr<NGAst::Stmt> parse_stmt();
        std::unique_ptr<NGAst::Expr> parse_expr();
    };
}
