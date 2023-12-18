#include "stdafx.h"
#include "ASMGenerator.h"

bool is_number(const std::string &str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it))
    {
        ++it;
    }

    return !str.empty() && it == str.end();
}

void ASMGenerator::create_asm(const std::string &file_path, const std::vector<Token> &tokens)
{
    std::ofstream file(file_path);
    if (file.fail())
    {
        spdlog::error("NOP");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i].type == TokenType::RETURN && tokens[i + 1].type == TokenType::VARIABLE)
        {
            if (is_number(tokens[i + 1].value))
            {
                mov("rax", 60);
                mov("rdi", atoi(tokens[i + 1].value.c_str()));
                syscall();
            }
        }
    }

    file << stream.str();
}
