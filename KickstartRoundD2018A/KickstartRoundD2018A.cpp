#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

string solve()
{
    long long int ans = LLONG_MIN;

    long long int N, O, D, X1, X2, A, B, C, M, L;
    cin >> N >> O >> D >> X1 >> X2 >> A >> B >> C >> M >> L;

    vector<long long int> S(N);
    S[0] = X1;
    S[1] = X2;

    for (int i = 2; i < N; i++)
        S[i] = (S[i - 1] * A + S[i - 2] * B + C) % M;

    for (int i = 0; i < N; i++) { // i : start index
        long long int sum = 0;
        long long int odds = 0;
        for (int j = i; j < N; j++) {
            sum += S[j] + L;
            odds += (S[j] + L) % 2 ? 1 : 0;
            if (odds > O)
                break;
            if (sum <= D && sum > ans)
                ans = sum;
        }
    }

    if (ans == LLONG_MIN)
        return "IMPOSSIBLE";
    else
        return to_string(ans);
}

int main()
{
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++)
        cout << "Case #" << to_string(i) << ": " << solve()<< endl;
}