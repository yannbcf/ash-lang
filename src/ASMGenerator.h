#pragma once

#include "Parser.h"
#include <sstream>

class ASMGenerator
{
public:
    ASMGenerator()
    {
        stream << "extern printf\n\nsection .text\nglobal _start\n_start:\n";
    }

    void create_asm(const std::string &file_path, const std::vector<Token> &tokens);

    template <typename T>
    inline void mov(const std::string &reg, const T &value)
    {
        stream << std::format("    mov {}, {}", reg, value) << "\n";
    }

    inline void syscall()
    {
        stream << "    syscall\n";
    }

private:
    std::stringstream stream{};
};
