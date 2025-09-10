#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

namespace amanita {
const auto not_space = [](unsigned char c) {
    return !std::isspace(c);
};

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::ranges::find_if(s, not_space));
}

inline void rtrim(std::string &s) {
    s.erase(std::ranges::find_if(s | std::views::reverse, not_space).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter);
std::vector<std::string> split(const std::string &s, char delimiter);
} // namespace amanita
