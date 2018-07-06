#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

int N;
int phi[1000];
bool visited[1000];
int curStart;

int getNextStart()
{
    int i = curStart + 1;
    for (; i < N; i++)
        if (!visited[i])
            break;
    return i;
}

void solve()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &phi[i]);
        phi[i]--; // 0-base로 번호 매기기 위해서
        visited[i] = false;
    }
    curStart = -1;

    int ans = 0;
    while ((curStart = getNextStart()) < N) {
        int cur = curStart;
        visited[cur] = true;
        while (phi[cur] != curStart) {
            cur = phi[cur];
            visited[cur] = true;
        }
        ans++;
    }

    printf("%d\n", ans);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
}