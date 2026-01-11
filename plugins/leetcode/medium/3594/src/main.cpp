/**
 * https://leetcode.com/problems/loud-and-rich/description/?envType=problem-list-v2&envId=graph
 */
#include <cstdio>
#include <vector>
#include "plugin_api.h"
#include "utils.h"

using namespace std;

static PluginInfo info {
    "3594",
    "Minimum Time to Transport All Individuals",
    PLUGIN_API_VERSION
};
struct TestCase {
    int n,k,m;
    vector<int> time;
    vector<double> mul;
};

double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
    double ret = .0F;
    return ret;
}

extern "C" {
    PLUGIN_API PluginInfo* plugin_info() {
        return &info;
    }

    PLUGIN_API void plugin_do_test(void) {
        vector<TestCase> test = {
             {1, 1, 2, common::convertToVector("[5]"), common::convertToDoubleVector("[1.0,1.3]")},
             {3, 2, 3, common::convertToVector("[2,5,8]"), common::convertToDoubleVector("[1.0,1.5,0.75]")},
             {2, 1, 2, common::convertToVector("[10,10]"), common::convertToDoubleVector("[2,2]")}
        };
        for (auto i:test) {
            minTime(i.n, i.k, i.m, i.time, i.mul);
        }
    }
}
