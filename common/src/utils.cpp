#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

#include <string>
#include <vector>
#include <sstream>
#include "utils.h"

namespace common {
using namespace std;

std::string decorate(const std::string& text) {
    return "[[" + text + "]]";
}

std::vector<int> convertToVector(const std::string& str) {
    vector<int> ret;
    if (str.empty()) return ret;
    string tmp = "";
    for (int i =0; i<str.length(); ++i) {
        char ch = str.at(i);
        if (ch >= '0' && ch <= '9') {
            tmp += ch;
        } else {
            if (ch == ',' || ch == ']') {
                if (!tmp.empty()) {
                    stringstream ss(tmp);
                    int n;
                    ss >> n;
                    ret.push_back(n);
                    tmp = "";
                }
            }
        }
    }
    return ret;
}

std::vector<std::vector<int> > convert(const std::string& str) {
    vector<vector<int>> ret;
    if (str.empty()) return ret;
    string tmp = "";
    vector<int> ent;
    for (int i =0; i<str.length()-1; ++i) {
        char ch = str.at(i);
        if (ch >= '0' && ch <= '9') {
            tmp += ch;
        } else {
            if (ch == ',' || ch == ']') {
                if (!tmp.empty()) {
                    stringstream ss(tmp);
                    int n;
                    ss >> n;
                    ent.push_back(n);
                    tmp = "";
                }
            }
            if (ch == ']') {
                ret.push_back(ent);
                ent.clear();
            }
        }
    }
    return ret;
}

#ifdef _WIN32
std::vector<std::string> list_libraries(const std::string& path) {
    std::vector<std::string> files;
    std::string search = path + "\\*.dll";
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(search.c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            files.push_back(path + "\\" + fd.cFileName);
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
    return files;
}
#else
std::vector<std::string> list_libraries(const std::string& path) {
    std::vector<std::string> files;
    DIR* dir = opendir(path.c_str());
    if (!dir) return files;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (filename.size() > 3 && filename.substr(filename.size()-3) == ".so") {
            files.push_back(path + "/" + filename);
        }
    }
    closedir(dir);
    return files;
}
#endif
}
