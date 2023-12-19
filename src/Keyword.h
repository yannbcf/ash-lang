#pragma once

#include <unordered_map>
#include <functional>
#include <string>

#include "Parser.h"

class Keyword
{
    static auto &All()
    {
        static std::unordered_map<std::string, Keyword *> all;
        return all;
    }

public:
    using Callback = std::function<void(Parser *, const std::string &)>;
    Callback callback;

    Keyword(const std::string &_name, Callback _callback) : name(_name), callback(_callback)
    {
        All()[name] = this;
    };

    static Keyword *Get(const std::string &name)
    {
        if (auto it = All().find(name); it != All().end())
        {
            return it->second;
        }

        return nullptr;
    }

private:
    std::string name;
};

static Keyword returnKeyword("return", [](Parser *parser, const std::string &value)
                             { parser->tokens.push_back(Token(Token::RETURN, value)); });