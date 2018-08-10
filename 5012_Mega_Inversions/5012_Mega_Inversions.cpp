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

int main()
{
    int n;
    scanf("%d", &n);

    SegTree st_2more(n);
    SegTree st_1more(n);

    st_2more.build_tree(0, 0, n - 1);
    st_1more.build_tree(0, 0, n - 1);

    unsigned long long ans = 0;

    int n_ = n;
    while (n_--) {
        int a;
        scanf("%d", &a);

        a--;

        st_2more.inc(a, 1);
        st_1more.inc(a, st_2more.find_sum(0, a + 1, n - 1, 0, n - 1));
        ans += st_1more.find_sum(0, a + 1, n - 1, 0, n - 1);
    }
    printf("%llu\n", ans);
    scanf("%d", &n);
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