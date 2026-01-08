/**
 * https://leetcode.com/problems/find-eventual-safe-states/description/?envType=problem-list-v2&envId=graph
 */

#include "plugin_api.h"
#include "utils.h"

static PluginInfo info {
    "802",
    "Find Eventual Safe States",
    PLUGIN_API_VERSION
};

extern "C" {

PLUGIN_API PluginInfo* plugin_info() {
    return &info;
}

PLUGIN_API void plugin_do_test(void) {
    int value = 19;
    printf("[%d], [%s], ans = [%d]\n", info.id, info.name, common::clamp(value + 1, 0, 100));
}

}
