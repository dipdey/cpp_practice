/**
 * https://leetcode.com/problems/loud-and-rich/description/?envType=problem-list-v2&envId=graph
 */
#include <cstdio>
#include <vector>
#include "plugin_api.h"
#include "utils.h"

using namespace std;

static PluginInfo info {
    "851",
    "Loud and Rich",
    PLUGIN_API_VERSION
};
struct TestCase {
    vector<vector<int>> richer;
    vector<int> quiet;
};

void dfs(const vector<vector<int>>&adj, const vector<int>& quiet, int u, vector<bool> &visited, vector<int> &smaller) {
    visited[u] = true;

    for (auto v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, quiet, v, visited, smaller);
        }
        if (quiet[smaller[v]] < quiet[smaller[u]]) {
            smaller[u] = smaller[v];
        }
    }
}
void dfs2(const vector<vector<int>>&adj, const vector<int>& quiet, int u, vector<bool> &visited, vector<int> &smaller) {
    visited[u] = true;

    for (auto v : adj[u]) {
        if (quiet[smaller[v]] < quiet[smaller[u]]) {
            smaller[u] = smaller[v];
        }
        if (!visited[v]) {
            dfs(adj, quiet, v, visited, smaller);
        }
    }
}
vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    const size_t n = quiet.size();
    vector<vector<int>> adj(n, vector<int>());
    for (auto &i : richer) {
        adj[i[1]].push_back(i[0]);
    }
    vector<bool> visited(n, false);
    vector<int> smaller;
    for (size_t u = 0; u<n; ++u) {
        smaller.push_back(smaller.size());
    }
    for (size_t u = 0; u<n; ++u) {
        if (!visited[u]) {
            dfs(adj, quiet, u, visited, smaller);
        }
    }
    visited.assign(n, false);
    for (size_t u = 0; u<n; ++u) {
        if (!visited[u]) {
            dfs2(adj, quiet, u, visited, smaller);
        }
    }

    return smaller;
}

extern "C" {
    PLUGIN_API PluginInfo* plugin_info() {
        return &info;
    }

    PLUGIN_API void plugin_do_test(void) {
        vector<TestCase> test = {
            {common::convert("[[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]]"), common::convertToVector("[3,2,5,4,6,1,7,0]")},
            {common::convert("[]"), common::convertToVector("[0]")}
        };
        for (auto i:test) {
            loudAndRich(i.richer, i.quiet);
        }
    }
}
