/**
 * https://leetcode.com/problems/keys-and-rooms/description/?envType=problem-list-v2&envId=graph
 */

#include <cstdio>
#include <vector>
#include "plugin_api.h"
#include "utils.h"

using namespace std;

static PluginInfo info {
    "841",
    "Keys and Rooms",
    PLUGIN_API_VERSION
};

void dfs(const vector<vector<int>>&adj, int u, vector<bool> &visited) {
    visited[u] = true;

    for (auto v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, v, visited);
        }
    }
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    const size_t n = rooms.size();
    vector<bool> visited (n, false);
    dfs(rooms, 0, visited);
    for (auto b : visited) {
        if (!b) return false;
    }
    return true;
}

extern "C" {
    PLUGIN_API PluginInfo* plugin_info() {
        return &info;
    }

    PLUGIN_API void plugin_do_test(void) {
        vector<vector<vector<int>>> test = {
            common::convert("[[1],[2],[3],[]]"),
            common::convert("[[1,3],[3,0,1],[2],[0]]")
        };
        for (auto i:test) {
            canVisitAllRooms(i);
        }
    }
}
