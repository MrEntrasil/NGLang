#pragma once
#include <cstdint>
#include <vector>

namespace NGLang {
  namespace Runtime {
    class VirtualMachine {
    private:
      const Bytecode::BytecodeStream* bytecodes;
      const std::vector<uint32_t>* constants;
      std::vector<uint32_t> stack;
      std::vector<uint32_t> registers;
      uint32_t program_counter;
      uint32_t stack_pointer;
      uint32_t base_pointer;
      bool zero_flag;
      bool carry_flag;
      bool sign_flag;
      bool overflow_flag;

      void execute_instruction(const Bytecode::Instruction& instr);
      uint32_t pop_stack();
      void push_stack(uint32_t value);

    public:
      VirtualMachine();
      void load_program(const Bytecode::BytecodeStream& bc, const std::vector<uint32_t> consts);
      bool execute();
      virtual uint32_t sys_call(uint32_t call_number, uint32_t arg1 = 0, uint32_t arg2 = 0, uint32_t arg3 = 0);
    };
  }
}
