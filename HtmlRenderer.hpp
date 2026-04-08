#pragma once

#include "Token.hpp"
#include <string>
#include <sstream>

class HtmlRenderer {
public:
    std::string generateColoredHTML(const std::vector<Token>& tokens);
};
