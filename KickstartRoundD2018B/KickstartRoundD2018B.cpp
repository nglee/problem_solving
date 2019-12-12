#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

string solve()
{
    long long int ans = 0LL;

    long long int N, K, p1, p2, A1, B1, C1, M1, h1, h2, A2, B2, C2, M2,
        x1, x2, A3, B3, C3, M3, y1, y2, A4, B4, C4, M4;
    cin >> N >> K >> p1 >> p2 >> A1 >> B1 >> C1 >> M1
        >> h1 >> h2 >> A2 >> B2 >> C2 >> M2
        >> x1 >> x2 >> A3 >> B3 >> C3 >> M3
        >> y1 >> y2 >> A4 >> B4 >> C4 >> M4;
    vector<long long int> p(N), h(N), x(K), y(K);
    p[0] = p1; p[1] = p2;
    h[0] = h1; h[1] = h2;
    x[0] = x1; x[1] = x2;
    y[0] = y1; y[1] = y2;
    for (int i = 2; i < N; i++) {
        p[i] = (p[i - 1] * A1 + p[i - 2] * B1 + C1) % M1 + 1;
        h[i] = (h[i - 1] * A2 + h[i - 2] * B2 + C2) % M2 + 1;
    }
    for (int i = 2; i < K; i++) {
        x[i] = (x[i - 1] * A3 + x[i - 2] * B3 + C3) % M3 + 1;
        y[i] = (y[i - 1] * A4 + y[i - 2] * B4 + C4) % M4 + 1;
    }

    #pragma omp parallel for
    for (int i = 0; i < K; i++)
        for (int j = 0; j < N; j++)
            if (abs(x[i] - p[j]) <= h[j] - y[i]) {
                #pragma omp critical
                ans++;
                break;
            }

    return to_string(ans);
}

int main()
{
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++)
        cout << "Case #" << to_string(i) << ": " << solve() << endl;
    //cin >> T;
}