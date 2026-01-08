#pragma once

#ifdef _WIN32
  #ifdef PLUGIN_EXPORTS
    #define PLUGIN_API __declspec(dllexport)
  #else
    #define PLUGIN_API __declspec(dllimport)
  #endif
#else
  #define PLUGIN_API
#endif

extern "C" {

// Increment if ABI changes
static const int PLUGIN_API_VERSION = 1;

struct PluginInfo {
    int id;
    const char* name;
    int api_version;
};

/**
 * Must be implemented by every plugin
 */
PLUGIN_API PluginInfo* plugin_info();

/**
 * Example exported function
 */
PLUGIN_API int plugin_compute(int value);

}
