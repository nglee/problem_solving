#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

class SegTree
{
public:
    SegTree(int num_elems)
    {
        a = make_unique<vector<long long>>(num_elems);
        tree = make_unique<vector<long long>>(powl(2, ceill(log2l(num_elems)) + 1) - 1);
    }

    long long build_tree(long long node, long long start, long long end)
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

    void replace(long long idx, long long val)
    {
        long long tree_idx = a->at(idx);
        long long diff = val - tree->at(tree_idx);
        tree->at(tree_idx) = val;
        while (tree_idx != 0) {
            tree_idx = (tree_idx + 1) / 2 - 1;
            tree->at(tree_idx) += diff;
        }
    }

    long long find_sum(long long node, long long start, long long end, long long node_left, long long node_right)
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

    unique_ptr<vector<long long>> a;
    unique_ptr<vector<long long>> tree;
};

int main()
{
    long long N, M, K;
    scanf("%lld %lld %lld", &N, &M, &K);

    SegTree st(N);

    for (int i = 0; i < N; i++)
        scanf("%lld", &st.a->at(i));

    st.build_tree(0, 0, N - 1);

    long long count = M + K;
    while (count--) {
        long long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        if (a == 1)
            st.replace(b - 1, c);
        else
            printf("%lld\n", st.find_sum(0, b - 1, c - 1, 0, N - 1));
    }
}