/**
 * https://leetcode.com/problems/minimize-malware-spread/description/?envType=problem-list-v2&envId=graph
 */
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "plugin_api.h"
#include "utils.h"

using namespace std;

static PluginInfo info {
    "924",
    "Minimize Malware Spread",
    PLUGIN_API_VERSION
};
struct TestCase {
    vector<vector<int>> graph;
    vector<int> initial;
};

void dfs(const vector<vector<int>>& graph, const vector<bool>&infected, 
    int u, int id, vector<bool>&visited, unordered_map<int, pair<int, int> > &cc) {
    cc.emplace(id, pair<int, int>(0, 0));
    visited[u] = true;
    cc[id].second++;
    if (infected[u]) {
        cc[id].first++;
    }
    for (int v = 0; v<graph[u].size(); ++v) {
        if (graph[u][v] == 1 && !visited[v]) {
            dfs(graph, infected, v, id, visited, cc);
        }
    }
}
// Lets try new
int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int ret = 0;
    const size_t n = graph.size();
    unordered_map<int, pair<int, int> > cc;
    sort(initial.begin(), initial.end());
    vector<bool> infected(graph.size(), false);
    for (auto i : initial) {
        infected[i] = true;
    }
    vector<bool> visited(n, false);
    for (auto i : initial) {
        if (!visited[i]) {
            dfs(graph, infected, i, i, visited, cc);
        }
    }
    return ret;
}

extern "C" {
    PLUGIN_API PluginInfo* plugin_info() {
        return &info;
    }

    PLUGIN_API void plugin_do_test(void) {
        vector<TestCase> test = {
            {common::convert("[[1,1,0],[1,1,0],[0,0,1]]"), common::convertToVector("[0,1]")}
        };
        for (auto i:test) {
            minMalwareSpread(i.graph, i.initial);
        }
    }
}
