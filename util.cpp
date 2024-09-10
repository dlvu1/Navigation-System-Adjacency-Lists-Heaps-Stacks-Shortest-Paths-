#include "util.h"
#include <sstream>
#include <iostream> 

std::vector<std::string> Util::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void Util::showError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}