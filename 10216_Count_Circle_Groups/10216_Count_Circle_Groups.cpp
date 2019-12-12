//#include <iostream>
//#include <unordered_set>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//unsigned short XYR[3000][3];
//
//#define square(a) ((a) * (a))
//
//bool meet(const int a, const int b)
//{
//    unsigned int a_x = XYR[a][0];
//    unsigned int a_y = XYR[a][1];
//    unsigned int a_r = XYR[a][2];
//    unsigned int b_x = XYR[b][0];
//    unsigned int b_y = XYR[b][1];
//    unsigned int b_r = XYR[b][2];
//
//    return square(a_r + b_r) >= square(b_x - a_x) + square(b_y - a_y);
//}
//
//void solve()
//{
//    int N;
//    cin >> N;
//
//    vector<unordered_set<short>> groups;
//
//    for (int i = 0; i < N; i++) {
//        cin >> XYR[i][0] >> XYR[i][1] >> XYR[i][2];
//
//        int curIdx = groups.size();
//        unordered_set<short> newgroup;
//        newgroup.insert(i);
//        groups.emplace_back(newgroup);
//
//        for (int groupIdx = 0; groupIdx < groups.size(); groupIdx++) {
//            if (groupIdx == curIdx)
//                continue;
//
//            unordered_set<short>& group = groups[groupIdx];
//
//            bool met = false;
//            for (auto& pointIdx : group)
//                if (meet(i, pointIdx)) {
//                    met = true;
//                    break;
//                }
//
//            if (met) {
//                if (groups[curIdx].size() < group.size()) {
//                    group.insert(groups[curIdx].begin(), groups[curIdx].end());
//                    groups[curIdx] = groups[groups.size() - 1];
//                    if (groupIdx != groups.size() - 1)
//                        curIdx = groupIdx;
//                } else {
//                    groups[curIdx].insert(group.begin(), group.end());
//                    group = groups[groups.size() - 1];
//                    if (curIdx == groups.size() - 1)
//                        curIdx = groupIdx;
//                }
//                groups.pop_back();
//            }
//        }
//    }
//
//    cout << groups.size() << endl;
//}
//
//int main()
//{
//    int T;
//    cin >> T;
//    while (T--)
//        solve();
//}

#include <iostream>
#include <vector>

using namespace std;

int xyr[3000][3];

#define square(a) ((a) * (a))

bool meet(const int a, const int b)
{
    int a_x = xyr[a][0];
    int a_y = xyr[a][1];
    int a_r = xyr[a][2];
    int b_x = xyr[b][0];
    int b_y = xyr[b][1];
    int b_r = xyr[b][2];

    return square(a_r + b_r) >= square(b_x - a_x) + square(b_y - a_y);
}

struct DisjointSet {
    vector<int> parent;
    DisjointSet(int n)
    {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int idx)
    {
        if (parent[idx] == idx)
            return idx;
        else
            return find(parent[idx]);
    }

    void merge(int a, int b)
    {
        int u = find(a), v = find(b);
        if (u != v)
            parent[u] = v;
    }
};

void solve_unionfind()
{
    int N;
    cin >> N;

    DisjointSet ds(N);

    for (int i = 0; i < N; i++)
        cin >> xyr[i][0] >> xyr[i][1] >> xyr[i][2];

    for (int i = 1; i < N; i++)
        for (int j = 0; j < i; j++)
            if (meet(i, j))
                ds.merge(i, j);

    int count = 0;
    vector<bool> counted(N);
    for (int i = 0; i < N; i++)
    {
        int root = ds.find(i);
        if (counted[root])
            continue;
        count++;
        counted[root] = true;
    }

    cout << count << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve_unionfind();
    cin >> T;
}