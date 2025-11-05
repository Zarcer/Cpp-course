#include "regex.hpp"
#include <cctype>
#include <stdexcept>

bool Token::matches(char c) const {
    if (type == DOT) return true;
    if (type == CHAR) return c == chars[0];
    return chars.find(c) != std::string::npos;
}

void Regex::parse(const std::string &p) {
    for (size_t i = 0; i < p.size();) {
        char c = p[i];
        Token::Type type;
        std::string chars;
        if (c == '.') {
            type = Token::DOT;
            ++i;
        } else if (c == '[') {
            type = Token::CLASS;
            ++i;
            while (i < p.size() && p[i] != ']') {
                if (i + 2 < p.size() && p[i+1] == '-') {
                    for (char ch = p[i]; ch <= p[i+2]; ++ch) chars.push_back(ch);
                    i += 3;
                } else chars.push_back(p[i++]);
            }
            if (i >= p.size() || p[i] != ']') throw std::runtime_error("Unclosed [");
            ++i;
        } else if (std::isalnum(c) || c == ' ') {
            type = Token::CHAR;
            chars = c;
            ++i;
        } else throw std::runtime_error("No such symbol allowed");
        char quant = 0;
        if (i < p.size() && (p[i] == '*' || p[i] == '+' || p[i] == '?')) quant = p[i++];
        tokens.emplace_back(type, chars, quant);
    }
}

Regex::Regex(const std::string &pattern) { parse(pattern); }

bool Regex::match(const std::string &s) const {
    size_t pos = 0;
    for (size_t i = 0;i<tokens.size(); ++i) {
        const Token &tk = tokens[i];
        switch (tk.quant) {
            case 0:
                if (pos >= s.size() || !tk.matches(s[pos++])) return false;
                break;
            case '*':
                while (pos < s.size() && tk.matches(s[pos])) ++pos;
                break;
            case '+':
                if (pos >= s.size() || !tk.matches(s[pos++])) return false;
                while (pos < s.size() && tk.matches(s[pos])) ++pos;
                break;
            case '?':
                size_t saved = pos;
                if (pos < s.size() && tk.matches(s[pos])) {
                    size_t nextPos = pos+1;
                    if (i+1<tokens.size()) {
                        const Token &next = tokens[i+1];
                        if (next.quant==0&&next.matches(s[pos])) {
                            pos=saved;
                        }
                        else {
                            pos=nextPos;
                        }
                    }
                    else {
                        pos = nextPos;
                    }
                }
                break;
        }
    }
    return pos == s.size();
}