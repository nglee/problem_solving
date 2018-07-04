#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve()
{
    int N;
    cin >> N;
    int N_ = N;
    vector<pair<int, int>> stops;
    while (N_--)
    {
        pair<int, int> stop;
        int a, b;
        cin >> a >> b;
        stop.first = a;
        stop.second = b;
        stops.emplace_back(stop);
    }
    int P;
    cin >> P;
    int P_ = P;
    vector<int> targets;
    vector<int> count(P, 0);
    while (P_--)
    {
        int target;
        cin >> target;
        targets.emplace_back(target);
    }
    for (int i = 0; i < N; i++)
    {
        pair<int, int> stop = stops[i];
        for (int j = 0; j < P; j++)
        {
            int target = targets[j];
            if (target >= stop.first && target <= stop.second)
                count[j]++;
        }
    }
    for (int i = 0; i < P; i++)
        cout << " " << to_string(count[i]);
    cout << "\n";
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        cout << "Case #" << to_string(i) << ":";
        solve();
    }
}