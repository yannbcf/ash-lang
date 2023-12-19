#pragma once

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
    std::vector<Token> tokens{};

    Parser(const std::string &filePath) : filePath(filePath){};
    [[nodiscard]] std::vector<Token> parseFile();

private:
    std::string filePath;

    Token parse_character(const char c);
};
