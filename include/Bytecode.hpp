#pragma once
#include <vector>

namespace NGLang {
  namespace Bytecode {
    enum class OpCode {
      PUSH, POP,
      
      ADD, SUB, MUL, DIV,
      INC, DEC, NEG,

      AND, OR, XOR, NOT,
      SHL, SHR,

      CMP, TEST,
      JE, JNE, JG, JGE, JL, JLE,

      JMP, CALL, RET, LOOP,

      LOAD, STORE, PUSH_REG, POP_REG,

      HALT, NOP, SYSCALL,

      IN, OUT
    };

    struct Instruction {
      OpCode opcode;
      uint32_t operand;
      Instruction(OpCode op, uint32_t opnd = 0) : opcode(op), operand(opnd) {}
    };

    using BytecodeStream = std::vector<Instruction>;
  }
}
