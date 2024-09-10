#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Util {
public:
    static std::vector<std::string> splitString(const std::string& input, char delimiter);
    static void showError(const std::string& message);
};

#endif // UTIL_H
