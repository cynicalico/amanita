#include "sops.hpp"

#include <sstream>

std::vector<std::string> amanita::split(const std::string &s, const std::string &delimiter) {
    const size_t delimiter_len = delimiter.length();

    size_t pos_start = 0, pos_end;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));

    return res;
}

std::vector<std::string> amanita::split(const std::string &s, const char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(s);

    std::string item;
    while (getline(ss, item, delimiter))
        result.push_back(item);

    return result;
}
