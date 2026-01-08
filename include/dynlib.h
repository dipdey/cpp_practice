#pragma once

#ifdef _WIN32
  #include <windows.h>
  using DynLibHandle = HMODULE;
#else
  #include <dlfcn.h>
  using DynLibHandle = void*;
#endif

inline DynLibHandle dynlib_open(const char* path) {
#ifdef _WIN32
    return LoadLibraryA(path);
#else
    return dlopen(path, RTLD_NOW);
#endif
}

inline void* dynlib_symbol(DynLibHandle lib, const char* name) {
#ifdef _WIN32
    return reinterpret_cast<void*>(GetProcAddress(lib, name));
#else
    return dlsym(lib, name);
#endif
}

inline void dynlib_close(DynLibHandle lib) {
#ifdef _WIN32
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif
}
