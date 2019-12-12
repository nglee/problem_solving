#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<unsigned long long> sums;

#if 1
// Solution with Segment Tree

#include <memory>
#include <cmath>

using namespace std;

class SegTree
{
public:
    SegTree(int num_elems)
    {
        a = make_unique<vector<unsigned long long>>(num_elems);
        tree = make_unique<vector<unsigned long long>>(powl(2, ceill(log2l(num_elems)) + 1) - 1);
    }

    unsigned long long build_tree(unsigned long long node, unsigned long long start, unsigned long long end)
    {
        if (start == end) {
            tree->at(node) = a->at(end);
            a->at(end) = node;
            return tree->at(node);
        }
        else {
            return tree->at(node) =
                build_tree((node + 1) * 2 - 1, start, (start + end) / 2)
                + build_tree((node + 1) * 2, (start + end) / 2 + 1, end);
        }
    }

    void replace(unsigned long long idx, unsigned long long val)
    {
        unsigned long long tree_idx = a->at(idx);
        unsigned long long diff = val - tree->at(tree_idx);
        tree->at(tree_idx) = val;
        propagate_up(tree_idx, diff);
    }

    void inc(unsigned long long idx, unsigned long long val)
    {
        unsigned long long tree_idx = a->at(idx);
        tree->at(tree_idx) += val;
        propagate_up(tree_idx, val);
    }

private:
    void propagate_up(unsigned long long tree_idx, unsigned long long diff)
    {
        while (tree_idx != 0) {
            tree_idx = (tree_idx + 1) / 2 - 1;
            tree->at(tree_idx) += diff;
        }
    }

public:
    unsigned long long find_sum(unsigned long long node, unsigned long long start, unsigned long long end, unsigned long long node_left, unsigned long long node_right)
    {
        if (end < node_left || start > node_right)
            return 0;
        else if (start <= node_left && node_right <= end)
            return tree->at(node);
        else
            return
                find_sum((node + 1) * 2 - 1, start, end, node_left, (node_left + node_right) / 2)
                + find_sum((node + 1) * 2, start, end, (node_left + node_right) / 2 + 1, node_right);
    }

    unique_ptr<vector<unsigned long long>> a;
    unique_ptr<vector<unsigned long long>> tree;
};

void solve()
{
    unsigned long long N, Q;
    cin >> N >> Q;

	vector<int> initial(N);
	for (int i = 0; i < N; i++)
		cin >> initial[i];

	vector<int> sums(N * (N + 1) / 2);
	int idx = 0;
	for (int i = 0; i < N; i++) {
		int partial_sum = 0;
		for (int j = i; j < N; j++)
	}


	SegTree st(N * (N + 1) / 2);


    for (unsigned long long i = 0; i < N; i++)
        fstr >> Ns[i];

    vector<unsigned long long> sums;
}

#else
void solve(ifstream& fstr)
{
    unsigned long long N, Q;
    fstr >> N >> Q;

    vector<unsigned long long> Ns(N);
    for (unsigned long long i = 0; i < N; i++)
        fstr >> Ns[i];

    vector<unsigned long long> sums;

    // Version 1 - O(n^3)
    //for (unsigned long long i = 1; i <= N; i++)
    //    for (unsigned long long j = 0; j + i <= N; j++)
    //        sums.emplace_back(accumulate(Ns.begin() + j, Ns.begin() + j + i, 0));

    // Version 2 - O(n^2)
    for (unsigned long long i = 0; i < N; i++) {
        int acc = 0;
        for (unsigned long long j = i; j < N; j++) {
            acc += Ns[j];
            sums.emplace_back(acc);
        }
    }

    sort(sums.begin(), sums.end());

    vector<pair<unsigned long long, unsigned long long>> queries(Q);
    for (unsigned long long i = 0; i < Q; i++) {
        fstr >> queries[i].first >> queries[i].second;
        queries[i].first--;
        queries[i].second--;
    }

    vector<unsigned long long> ans(Q, 0);
    for (unsigned long long i = 0; i < N * (N + 1) / 2; i++)
        for (unsigned long long q = 0; q < Q; q++)
            if (queries[q].first <= i && i <= queries[q].second)
                ans[q] += sums[i];

    for (unsigned long long q = 0; q < Q; q++)
        cout << ans[q] << "\n";
}
#endif

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << to_string(i) << ":\n";
		solve();
    }
    cin >> T;
}