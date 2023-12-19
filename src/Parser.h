#pragma once

#include <string>
#include <vector>
#include <set>

static std::set<char> CHAR_SET{'\n', '(', ')', ',', ';'};

struct Token
{
    enum Type
    {
        VARIABLE,
        ASSIGNMENT,
        OPEN_PAREN,
        CLOSE_PAREN,
        RETURN,
        INVALID,
    };

    std::string type_to_string(Type type)
    {
        switch (type)
        {
        case Token::VARIABLE:
            return "VARIABLE";
        case Token::ASSIGNMENT:
            return "ASSIGNMENT";
        case Token::OPEN_PAREN:
            return "OPEN_PAREN";
        case Token::CLOSE_PAREN:
            return "CLOSE_PAREN";
        case Token::RETURN:
            return "RETURN";
        }
    }

    Type type;
    std::string value;
};

class Parser
{
public:
    Parser(const std::string &file_path) : file_path(file_path){};
    [[nodiscard]] std::vector<Token> parse_file();

    void push_token(Token::Type type, const std::string &value)
    {
        tokens.push_back(Token(type, value));
    };

private:
    std::string file_path;
    std::vector<Token> tokens{};

    Token parse_character(const char c);
};
