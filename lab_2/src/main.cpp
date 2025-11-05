#include <iostream>
#include "regex.hpp"

int main() {
    std::string pattern;
    if (!std::getline(std::cin, pattern)) return 0;
    Regex re(pattern);
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << (re.match(line) ? "true" : "false") << '\n';
    }
}