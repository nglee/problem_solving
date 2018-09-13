#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

template <typename T = size_t>
class SegTree
{
    typedef size_t idx_t;

public:
    SegTree(idx_t num_elems)
    {
        a = make_unique<vector<T>>(num_elems);
        tree = make_unique<vector<T>>(powl(2, ceill(log2l(num_elems)) + 1) - 1);
    }

    void build_tree()
    {
        build_(0, 0, a->size() - 1);
    }

private:
    T build_(idx_t node, idx_t left, idx_t right)
    {
        if (left == right) {
            tree->at(node) = a->at(right);
            a->at(right) = node;
            return tree->at(node);
        }
        else {
            return tree->at(node) =
                build_((node + 1) * 2 - 1, left, (left + right) / 2)
                + build_((node + 1) * 2, (left + right) / 2 + 1, right);
        }
    }

public:
    void replace(idx_t idx, T val)
    {
        idx_t tree_idx = a->at(idx);
        T diff = val - tree->at(tree_idx);
        tree->at(tree_idx) = val;
        propagate_up(tree_idx, diff);
    }

    void inc(idx_t idx, T val)
    {
        idx_t tree_idx = a->at(idx);
        tree->at(tree_idx) += val;
        propagate_up(tree_idx, val);
    }

private:
    void propagate_up(idx_t tree_idx, T diff)
    {
        while (tree_idx != 0) {
            tree_idx = (tree_idx + 1) / 2 - 1;
            tree->at(tree_idx) += diff;
        }
    }

public:
    T find_sum(idx_t start, idx_t end)
    {
        return find_sum(0, start, end, 0, a->size() - 1);
    }

private:
    T find_sum(idx_t node, idx_t start, idx_t end, idx_t node_left, idx_t node_right)
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

public:
    unique_ptr<vector<T>> a;
    unique_ptr<vector<T>> tree;
};

void solve()
{
    int N;
    scanf("%d", &N);

    vector<int> tmp(N);

    SegTree<unsigned long long> st(N * 2); // -(N-1) <= value <= (n-1)
    st.build_tree();

    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);
        tmp[a - 1] = i;
    }

    unsigned long long ans = 0;
    int e1 = -2;
    int e2 = -1;
    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);

        long long value1 = tmp[a - 1] - i;
        unsigned long long value2 = value1 + (N - 1); // shift to make unsigned

        ans += st.find_sum(value2 + e2, 2 * N - 1);
        st.inc(value2 + e1, 1);

        e1++;
        e2++;
    }
    printf("%llu\n", ans);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) solve();
}