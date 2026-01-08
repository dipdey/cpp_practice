#pragma once

#include <vector>
#include <string>

namespace common {

inline int clamp(int v, int lo, int hi) {
    return (v < lo) ? lo : (v > hi) ? hi : v;
}

std::string decorate(const std::string& text);

std::vector<std::string> list_dlls(const std::string& path);
}
