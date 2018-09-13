#include <string>
#include <iostream>
#include <vector>

using namespace std;

string combine(vector<vector<bool>>& img, int x, int y, int l)
{
    if (l == 1) {
        return img[y][x] ? "1" : "0";
    } else {
        string lt = combine(img, x, y, l / 2);
        string rt = combine(img, x + l / 2, y, l / 2);
        string lb = combine(img, x, y + l / 2, l / 2);
        string rb = combine(img, x + l / 2, y + l / 2, l / 2);
        if (lt.length() == 1 && lt == rt && lt == lb && lt == rb) {
            return lt;
        } else {
            return "(" + lt + rt + lb + rb + ")";
        }
    }
}

int main()
{
    int N;
    cin >> N;
    vector<vector<bool>> img(N, vector<bool>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            char c;
            cin >> c;
            img[i][j] = (c == '1');
        }
    cout << combine(img, 0, 0, N);
}