#include "../src/regex.hpp"
#include <iostream>
#include <cassert>

int main() {
    Regex r1("a*a");
    assert(!r1.match("aa"));

    Regex r2("a?a");
    assert(r2.match("a"));

    Regex r3("[a-z]+[0-9]");
    assert(r3.match("abc1"));
    assert(!r3.match("abc"));

    Regex r4(".*");
    assert(r4.match("hello world"));

    Regex r5("[abc]?a");
    assert(r5.match("ba"));

    std::cout << "All tests passed!\n";
}