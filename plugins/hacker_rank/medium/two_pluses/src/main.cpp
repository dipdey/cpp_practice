/**
 * https://www.hackerrank.com/challenges/two-pluses/problem
 * Ema's Supercomputer
 */
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

#include "plugin_api.h"

using namespace std;

static PluginInfo info {
    "Ema_Supercomputer",
    "Ema's Supercomputer",
    PLUGIN_API_VERSION
};

const std::string input_path = INPUT_LOC;
const string proj_path = input_path;

static vector<string> split(const string &str);
static int readTestCase(const string &file, vector<string> &grid);

// Find the two largest valid pluses that can be drawn on "good" cells

struct Node {
    int sz, cost;
    // int x, y; // top left cell pos of the bounding box of the plus
    int r, c, k;

    bool operator < (const Node&that) const {
        if (r < that.r) {
            return true;
        } else if (r == that.r) {
            return c < that.c;
        }
        return false;
    }
    /**
     * IMPORTANT
     * how to check two plus sign on a 2D grid
     */
    bool isOverlapping(const Node&that) const {
        // 1️⃣ A vertical vs B vertical
        if (c == that.c) {
            int top = max(r - k, that.r - that.k);
            int bottom = min(r + k, that.r + that.k);
            if (top <= bottom) return true;
        }

        // 2️⃣ A horizontal vs B horizontal
        if (r == that.r) {
            int left = max(c - k, that.c - that.k);
            int right = min(c + k, that.c + that.k);
            if (left <= right) return true;
        }

        // 3️⃣ A vertical vs B horizontal
        if (between(that.r, r - k, r + k) && between(c, that.c - that.k, that.c + that.k))
            return true;
        
        // 4️⃣ A horizontal vs B vertical
        if (between(r, that.r - that.k, that.r + that.k) && between(that.c, c - k, c + k))
            return true;

        return false;
    }
private:
    // check if a point lies within a segment [a,b]
    bool between(int x, int a, int b) const {
        return x >= min(a,b) && x <= max(a,b);
    }
};

vector<Node> findMax(const vector<vector<int> > &grid, int sz) {
    vector<Node> ret;
    int R = grid.size();
    int C = grid[0].size();
    
    int id = 0;
    for (int i=0; i+sz<=R; ++i) {
        for (int j=0; j+sz<=C; ++j) {
            bool found = true;
            for (int k = 0, l = i; found && k<sz; ++k, ++l) {
                if (grid[l][j+sz/2] != 1 || grid[i+sz/2][l] != 1) {
                    found = false;
                }
            }
            if (found) {
                ret.push_back({sz, ++id, i+sz/2, j+sz/2, sz/2});
            }
        }
    }
    return ret;
}

int twoPluses(vector<string> gridStr) {
    vector<vector<int> > grid (gridStr.size(), vector<int>(gridStr[0].length(), 1)); // all good initially
    int C = min (grid.size(), grid[0].size());
    for (int i=0; i<gridStr.size(); ++i) {
        string r = gridStr[i];
        for (int j=0; j<r.length(); ++j) {
            grid[i][j] = (r[j] == 'B') ? 0 : 1;
        }
    }

    C = (C%2 == 0) ? C-1:C;
    vector<Node> full;
    for (int sz = C; sz>=1; sz-=2) {
        vector<Node> ret = findMax(grid, sz);
        if (ret.size() > 0) {
            full.insert(full.end(), ret.begin(), ret.end());
        }
    }
    sort(full.begin(), full.end());

    int best = 0;
    for (int i=0; i<full.size(); i++) {
        for (int j=i+1; j<full.size(); j++) {
            if (!full[i].isOverlapping(full[j])) {
                int k1 = (2*full[i].sz - 1);
                int k2 = (2*full[j].sz - 1);
                best = max(best, k1 * k2);
            }
        }
    }
    return best;
}

void testcase() {
    vector<string> gridStr;
    // readTestCase(proj_path+"test1.txt", gridStr);
    // readTestCase(proj_path+"input05.txt", gridStr);
    // readTestCase(proj_path+"input08.txt", gridStr);

    // readTestCase(proj_path+"input12.txt", gridStr);
    readTestCase(proj_path+"input14.txt", gridStr);
    
    twoPluses(gridStr);
}

extern "C" {

PLUGIN_API PluginInfo* plugin_info() {
    return &info;
}

PLUGIN_API void plugin_do_test(void) {
    testcase();
}
}

int readTestCase(const string &file, vector<string> &grid) {
    int total = 0;
    ifstream input(file);
    if (input.is_open()) {
        string word;
        getline(input, word);
        vector<string> words = split(word);
        int n = stoi(words[0]);
        int m = stoi(words[1]);
        grid.resize(n);

        for (int i=0; i<n; ++i) {
            getline(input, word);
            grid[i] = word;
        }
    }
    return total;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
