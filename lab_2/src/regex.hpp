#pragma once
#include <string>
#include <utility>
#include <vector>

class Token {
public:
    enum Type { CHAR, DOT, CLASS };
    Type type;
    std::string chars;
    char quant;
    explicit Token(Type t, std::string chars = "", char quant = 0): type(t), chars(std::move(chars)), quant(quant) {}
    bool matches(char c) const;
};

class Regex {
public:
    explicit Regex(const std::string &pattern);
    bool match(const std::string &text) const;

private:
    std::vector<Token> tokens;
    void parse(const std::string &pattern);
};