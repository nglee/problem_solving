#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m, n_, m_;
        scanf("%d %d", &n, &m);

        int X = 0, Y = 0;
            
        m_ = m;
        while (m_--)
        {
            int x;
            scanf("%d", &x);
            X = 10 * X + x;
        }

        m_ = m;
        while (m_--)
        {
            int y;
            scanf("%d", &y);
            Y = 10 * Y + y;
        }

        int wheel[110];

        for (int i = 0; i < n; i++)
        {
            int w;
            scanf("%d", &w);
            wheel[i] = w;
        }

        // 처음 m-1 개를 wheel 끝에 추가한다 (m <= n)
        for (int i = 0; i < m - 1; i++)
        {
            wheel[n + i] = wheel[i];
        }

        int val = 0;
        int tentom_1 = 1;
        for (int i = 0; i < m - 1; i++)
        {
            val = 10 * val + wheel[i];
            tentom_1 *= 10; // 나중에 활용하기 위해 10^(m-1) 값을 구한다
        }

        int count = 0;
        for (int i = 0; i < n; i++)
        {
            val = val * 10 + wheel[i + m - 1];
            if (val >= X && val <= Y)
                count++;
            val -= wheel[i] * tentom_1;
        }
        printf("%d\n", count);
    }
}