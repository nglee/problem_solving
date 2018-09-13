#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int H, W;
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        vector<char> tmp(W);
        for (int j = 0; j < W; j++)
            cin >> tmp[j];
        for (int j = W - 1; j >= 0; j--)
            cout << tmp[j];
        cout << "\n";
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}