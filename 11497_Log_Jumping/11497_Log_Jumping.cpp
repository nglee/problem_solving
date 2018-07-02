#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>

using namespace std;

int L[10000];

inline void solve()
{
    int N;
    scanf("%d", &N);
 
    for (int i = 0; i < N; i++)
        scanf("%d", &L[i]);

    sort(&L[0], &L[N]);

    int ans = 0;
    for (int i = 0; i < N - 2; i++)
        ans = max(ans, L[i + 2] - L[i]);

    printf("%d\n", ans);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
        solve();
}