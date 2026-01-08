#include <cstdio>
#include "plugin_api.h"
#include "utils.h"

static PluginInfo info {
    "841",
    "Keys and Rooms",
    PLUGIN_API_VERSION
};

extern "C" {

PLUGIN_API PluginInfo* plugin_info() {
    return &info;
}

PLUGIN_API void plugin_do_test(void) {
    int value = 17;
    printf("[%s], [%s], ans = [%d]\n", info.id, info.name, common::clamp(value * 5, 0, 100));
}

}
