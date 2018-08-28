#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
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

int main()
{
    int n;
    scanf("%d", &n);

    SegTree<unsigned long long> st_2more(n);
    SegTree<unsigned long long> st_1more(n);

    st_2more.build_tree();
    st_1more.build_tree();

    unsigned long long ans = 0;

    int n_ = n;
    while (n_--) {
        int a;
        scanf("%d", &a);

        a--;

        st_2more.inc(a, 1);
        st_1more.inc(a, st_2more.find_sum(a + 1, n - 1));
        ans += st_1more.find_sum(a + 1, n - 1);
    }
    printf("%llu\n", ans);
}

//#define _CRT_SECURE_NO_WARNINGS
//#include <cstdio>
//
//unsigned long long table[100000][2];
//// table[i][0] : i로 끝나는데 2개 더 붙일 수 있음
//// table[i][1] : i로 끝나는데 1개 더 붙일 수 있음
//
//int main()
//{
//    int n;
//    scanf("%d", &n);
//    unsigned long long ans = 0;
//
//    while (n--) {
//        int a;
//        scanf("%d", &a);
//        a--; // 배열 접근을 위한 인덱스
//
//        table[a][0]++;
//
//        for (int i = a + 1; i < 100000; i++) {
//            //if (table[i][1]) // if 문이 필요 없어짐
//                ans += table[i][1];
//            //if (table[i][0]) // 여기도
//                table[a][1] += table[i][0];
//        }
//    } 
//    printf("%llu\n", ans);
//    scanf("%d", &n);
//}