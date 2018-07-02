#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int L[1000000];

void solve()
{
    int N;
    scanf("%d", &N);
 
    for (int i = 0; i < N; i++)
        scanf("%d", &L[i]);

    long long int ans = 0;
    int sellprice = L[N - 1];

    for (int i = N - 2; i >= 0; i--)
    {
        if (L[i] > sellprice)
            sellprice = L[i];
        else
            ans += sellprice - L[i];
    }

    printf("%lld\n", ans);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
        solve();
}