#pragma once
#include <Bytecode.hpp>
#include <string>
#include <vector>

namespace NGLang {
  namespace Compiler {
    class Compiler {
    private:
      Bytecode::BytecodeStream bytecodes;
      std::vector<uint32_t> constants;
      
      void compile_expression(const std::string& expr);
      void compile_statement(const std::string& stmt);
      void compile_assignment(const std::string& assignment);
      void compile_control_flow(const std::string& flow_stmt);

    public:
      Compiler();
      bool compile(const std::string& src);
      std::string gen_c_code(const std::string& program = "program");
      bool save_c_code(const std::string& filename, const std::string& program);
    };
  }
}t
