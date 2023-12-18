#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <set>
#include <memory>

enum class TokenType
{
    VARIABLE,
    ASSIGNMENT,
    OPEN_PAREN,
    CLOSE_PAREN,
    RETURN,
};

struct Token
{
    TokenType type;
    std::string value;
};

class Parser
{
public:
    Parser(const std::string &filePath) : filePath(filePath){};
    [[nodiscard]] std::vector<Token> parseFile();

private:
    std::string filePath;

    std::vector<Token> tokens{};
    std::set<char> charSet{'\n', '(', ')', ',', ';'};
    std::unordered_map<std::string, std::function<void(const std::string &value)>> keywords{
        {"return", [&](const std::string &value)
         {
             tokens.push_back(Token{.type = TokenType::RETURN, .value = value});
         }}};

    std::unique_ptr<Token> parse_character(const char c);
};
