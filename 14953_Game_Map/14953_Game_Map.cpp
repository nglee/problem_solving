#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> cache;
vector<vector<int>> graph;
int cur_best = 0;

int dfs(const int& v)
{
    int ret = 0;
    int cur_edges = graph[v].size();

    for (const int& next_v : graph[v])
    {
        if (graph[next_v].size() <= cur_edges)
        {
            continue;
        }

        if (cache[next_v])
        {
            ret = max(ret, cache[next_v]);
        }
        else
        {
            ret = max(ret, dfs(next_v));
        }
    }

    ret++;

    if (ret > cur_best)
        cur_best = ret;

    cache[v] = ret;

    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    cache = vector<int>(n, 0);
    graph = vector<vector<int>>(n, vector<int>());

    while (m--)
    {
        int i, j;
        scanf("%d %d", &i, &j);

        graph[i].emplace_back(j);
        graph[j].emplace_back(i);
    }

    for (int v = n - 1; v >= 0; v--)
    {
        dfs(v);
    }

    printf("%d", cur_best);
}