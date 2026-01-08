#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

#include <string>
#include <vector>
#include "utils.h"

namespace common {

std::string decorate(const std::string& text) {
    return "[[" + text + "]]";
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
