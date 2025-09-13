#pragma once
#include <memory>
#include <iostream>
#include "Lexer.hpp"

namespace NGAst {
    struct Node {
        virtual ~Node() = default;
        virtual void print() const = 0;
    };
    struct Expr : Node {};
    struct LiteralExpr : Expr {
        std::string value;
        NGLexer::TokenType type;
        void print() const override {
            std::cout << value;
        }
        LiteralExpr(std::string& val, NGLexer::TokenType typ) : value(val), type(typ) {}
    };
    struct BinaryExpr : Expr {
        char op;
        std::unique_ptr<Expr> left;
        std::unique_ptr<Expr> right;
        void print() const override {
            // (45 + 7)
            std::cout << '('; left->print(); std::cout << ' ';
            std::cout << op << ' ';
            right->print(); std::cout << ')';
        }
        BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) :
        op(o), left(std::move(l)), right(std::move(r)) {}
    };
    struct Stmt : Node {};
    struct PrintStmt : Stmt {
        std::unique_ptr<Expr> expr;
    };
    struct VarDeclStmt : Stmt {
        std::string name;
        std::unique_ptr<Expr> init;
    };
}