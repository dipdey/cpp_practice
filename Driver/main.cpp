#include <iostream>
#include <filesystem>
#include <vector>
#include "dynlib.h"
#include "plugin_api.h"
#include "utils.h"

using namespace std;

struct LoadedPlugin {
    DynLibHandle handle;
    PluginInfo* info;
    void (*doTest)(void);
};

static void load_plugins(std::vector<LoadedPlugin> &plugins);

int main()
{
    std::vector<LoadedPlugin> plugins;
    load_plugins(plugins);

    while (true) {
        int id = -1;
        cout << "Avail Tests :: " << endl;
        // Use plugins
        for (int i = 0; i<plugins.size(); ++i) {
            auto &p = plugins[i];
            std::cout << i << ". " << p.info->id << ". [" << p.info->name << "]" << endl;
        }
        cout << "Enter your choise :: " << endl;
        cin >> id;
        bool correct = false;
        if (id < plugins.size()) {
            auto &p = plugins[id];
            p.doTest();
            correct = true;
        }
        if (!correct) {
            cout << "Invalid choice " << id << endl;
            break;
        }
    }
    // Cleanup
    for (auto &p : plugins)
    {
        dynlib_close(p.handle);
    }

    return 0;
}

void load_plugins(std::vector<LoadedPlugin> &plugins)
{
    const std::string pluginPath = PLUGIN_FOLDER;

    std::string plugin_dir = pluginPath; //"./plugins"; // path to your built plugins

    std::vector<std::string> files = common::list_dlls(plugin_dir);

    for (const auto &path : files)
    {
        DynLibHandle lib = dynlib_open(path.c_str());
        if (!lib)
        {
            std::cerr << "Failed to open: " << path << "\n";
            continue;
        }

        // read symbols
        auto info_fn = (PluginInfo * (*)()) dynlib_symbol(lib, "plugin_info");
        auto compute_fn = (void (*)(void))dynlib_symbol(lib, "plugin_do_test");

        if (!info_fn || !compute_fn)
        {
            std::cerr << "Missing symbols in: " << path << "\n";
            dynlib_close(lib);
            continue;
        }

        PluginInfo *info = info_fn();
        std::cout << "Loaded plugin: " << info->name
                  << ", API version: " << info->api_version << "\n";

        plugins.push_back({lib, info, compute_fn});
    }
}
