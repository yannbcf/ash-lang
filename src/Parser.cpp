#include "stdafx.h"
#include "Parser.h"

constexpr const char *token_type_to_string(TokenType e) noexcept
{
    switch (e)
    {
    case TokenType::VARIABLE:
        return "VARIABLE";
    case TokenType::ASSIGNMENT:
        return "ASSIGNMENT";
    case TokenType::OPEN_PAREN:
        return "OPEN_PAREN";
    case TokenType::CLOSE_PAREN:
        return "CLOSE_PAREN";
    case TokenType::RETURN:
        return "RETURN";
    }
}

std::unique_ptr<Token> Parser::parse_character(const char c)
{
    switch (c)
    {
    case '(':
        return std::make_unique<Token>(TokenType::OPEN_PAREN, std::string(1, c));
    case ')':
        return std::make_unique<Token>(TokenType::CLOSE_PAREN, std::string(1, c));
    case '=':
        return std::make_unique<Token>(TokenType::ASSIGNMENT, std::string(1, c));

    default:
        return nullptr;
    }
}

[[nodiscard]] std::vector<Token> Parser::parseFile()
{
    std::ifstream file(filePath);
    if (file.fail())
    {
        SPDLOG_ERROR("Could not find file at {}", filePath);
        exit(EXIT_FAILURE);
    }

    std::string buffer;
    char c;

    while (file.get(c))
    {
        if (!std::isspace(c) && !charSet.contains(c))
        {
            if (auto token = parse_character(c); token != nullptr)
            {
                tokens.push_back(*token.get());
                buffer.clear();
                continue;
            }

            buffer.push_back(c);
            continue;
        }

        if (auto it = keywords.find(buffer); it == keywords.end())
        {
            if (buffer.size() != 0)
            {
                tokens.push_back(Token{.type = TokenType::VARIABLE, .value = buffer});
                if (auto token = parse_character(c); token != nullptr)
                {
                    tokens.push_back(*token.get());
                }
            }
        }
        else
        {
            it->second(buffer);
        }

        buffer.clear();
    }

    for (const auto &token : tokens)
    {
        spdlog::info("{} : {}", static_cast<int>(token.type), token.value);
    }

    return tokens;
}
