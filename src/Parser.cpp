#include "stdafx.h"
#include "Keyword.h"
#include "Parser.h"

Token Parser::parse_character(const char c)
{
    switch (c)
    {
    case '(':
        return Token(Token::OPEN_PAREN, std::string(1, c));
    case ')':
        return Token(Token::CLOSE_PAREN, std::string(1, c));
    case '=':
        return Token(Token::ASSIGNMENT, std::string(1, c));

    default:
        return Token(Token::INVALID);
    }
}

std::vector<Token> Parser::parse_file()
{
    std::ifstream file(file_path);
    if (file.fail())
    {
        SPDLOG_ERROR("Could not find file at {}", file_path);
        exit(EXIT_FAILURE);
    }

    std::string buffer;
    char c;

    while (file.get(c))
    {
        if (!std::isspace(c) && !CHAR_SET.contains(c))
        {
            if (Token token = parse_character(c); token.type != Token::INVALID)
            {
                tokens.push_back(token);
                buffer.clear();
                continue;
            }

            buffer.push_back(c);
            continue;
        }

        if (Keyword *keyword = Keyword::Get(buffer); keyword != nullptr)
        {
            keyword->execute_callback(this, buffer);
        }
        else if (buffer.size() != 0)
        {
            tokens.push_back(Token(Token::VARIABLE, buffer));
            if (Token token = parse_character(c); token.type != Token::INVALID)
            {
                tokens.push_back(token);
            }
        }

        buffer.clear();
    }

    for (const auto &token : tokens)
    {
        spdlog::info("{} : {}", static_cast<int>(token.type), token.value);
    }

    return tokens;
}
