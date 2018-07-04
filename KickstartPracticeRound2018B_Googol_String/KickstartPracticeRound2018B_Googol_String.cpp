#include <iostream>
#include <vector>
#include <string>

using namespace std;

// IN : k >= 1
// OUT: first - smallest n that satisfies 2^(n-1) - 1 < k <= 2^n - 1
//      second - 2^n
pair<int, unsigned long long> find_n(const unsigned long long k)
{
    int n = 1;
    unsigned long long two_to_n = 2;
    while (1)
    {
        if (k <= two_to_n - 1)
            break;
        n++;
        two_to_n *= 2;
    }
    return pair<int, unsigned long long>(n, two_to_n);
}

bool solve(const unsigned long long k, const pair<int, unsigned long long> n, const bool one)
{
    if (k == 1)
        return one;
    
    unsigned long long two_to_n_1 = n.second / 2;

    if (k == two_to_n_1)
        return one;

    if (k < two_to_n_1)
        return solve(k, pair<int, unsigned long long>(n.first - 1, two_to_n_1), one);

    return solve(two_to_n_1 - (k - two_to_n_1), pair<int, unsigned long long>(n.first - 1, two_to_n_1), !one);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        unsigned long long K;
        cin >> K;
        cout << "Case #" << to_string(i) << ": " << to_string(solve(K, find_n(K), false)) << "\n";
    }
}