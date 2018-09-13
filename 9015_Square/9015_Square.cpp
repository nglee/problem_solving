#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

void solve()
{
    int N;
    scanf("%d", &N);
	map<pair<int, int>, int> coeff;
    for (int i = 0; i < N; i++) {
		pair<int, int> point;
        scanf("%d", &point.first);
        scanf("%d", &point.second);
		coeff.emplace(point, 1);
    }

    int max = 0;
	for (auto a : coeff)
		for (auto b = coeff.upper_bound(a.first); b != coeff.end(); b++) {
			pair<int, int> p1 = a.first;
			pair<int, int> p2 = (*b).first;
            int diffx = p2.first - p1.first;
            int diffy = p2.second - p1.second;

            int area = diffx * diffx + diffy * diffy;
            if (max >= area)
                continue;

            pair<int, int> cand1(p1.first + diffy, p1.second - diffx);
            pair<int, int> cand2(cand1.first + diffx, cand1.second + diffy);

            if (coeff.find(cand1) != coeff.end()
                && coeff.find(cand2) != coeff.end()) {
                max = area;
            }
        }
    printf("%d\n", max);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) solve();
    scanf("%d", &T);
}

#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
    int N;
    scanf("%d", &N);
    vector<pair<int, int>> coeff(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &coeff[i].first);
        scanf("%d", &coeff[i].second);
    }
    sort(coeff.begin(), coeff.end());

    int max = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int diffx = coeff[j].first - coeff[i].first;
            int diffy = coeff[j].second - coeff[i].second;

            int area = diffx * diffx + diffy * diffy;
            if (max >= area)
                continue;

            pair<int, int> cand1(coeff[i].first + diffy, coeff[i].second - diffx);
            pair<int, int> cand2(cand1.first + diffx, cand1.second + diffy);

            if (find(coeff.begin() + j + 1, coeff.end(), cand1) != coeff.end()
                && find(coeff.begin() + j + 1, coeff.end(), cand2) != coeff.end()) {
                max = area;
                continue;
            }

            pair<int, int> cand3(coeff[i].first - diffy, coeff[i].second + diffx);
            pair<int, int> cand4(cand3.first + diffx, cand3.second + diffy);

            if (find(coeff.begin() + j + 1, coeff.end(), cand3) != coeff.end()
                && find(coeff.begin() + j + 1, coeff.end(), cand4) != coeff.end())
                max = area;
        }
    printf("%d\n", max);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) solve();
    scanf("%d", &T);
}
#endif