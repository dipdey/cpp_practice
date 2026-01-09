/**
 * https://leetcode.com/problems/find-eventual-safe-states/description/?envType=problem-list-v2&envId=graph
 */
#include <vector>
#include <map>
#include "plugin_api.h"
#include "utils.h"

using namespace std;

static PluginInfo info {
    "802",
    "Find Eventual Safe States",
    PLUGIN_API_VERSION
};

void dfs(const vector<vector<int>>&adj, int u, vector<bool> &safe, vector<bool>&visited, vector<bool>&stack) {
    visited[u] = true;
    stack[u] = true;
    
    if (adj[u].size() == 0) { // terminal
        visited[u] = false;
        stack[u] = false;
        return;
    }

    for (auto v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, v, safe, visited, stack);
            if (!safe[v]) {
                safe[u] = false;
                break;
            }
        } else {
            if (stack[v]) {
                safe[u] = safe[v] = false;
                break;
            } else if (!safe[v]) {
                safe[u] = false;
                break;
            }
        }
    }
    stack[u] = false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    const size_t n = graph.size();
    vector<int> ret;
    vector<bool> safe(n, true), visited (n, false);
    for (size_t u=0; u<n; ++u) {
        if (!visited[u]) {
            vector<bool>stack(n, false);
            dfs(graph, u, safe, visited, stack);
        }
    }
    for (size_t i=0; i<n; ++i) {
        if (safe[i])
        ret.push_back(i);
    }
    return ret;
}

extern "C" {
    PLUGIN_API PluginInfo* plugin_info() {
        return &info;
    }

    PLUGIN_API void plugin_do_test(void) {
        vector<vector<vector<int>>> test = {
            common::convert("[[],[0,2,3,4],[3],[4],[]]"),
            common::convert("[[1,2],[2,3],[5],[0],[5],[],[]]"),
            common::convert("[[0],[2,3,4],[3,4],[0,4],[]]")
        };
        for (auto &graph : test)
        eventualSafeNodes(graph);
    }
}
