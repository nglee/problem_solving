#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        string N;
        cin >> N;

        string ans;

        if (N.size() == 1)
        {
            ans = N;
        }
        else
        {
            ans += N[0];
            for (int i = 1; i < N.size(); i++)
            {
                ans += N[i];

                if (N[i - 1] > N[i])
                {
                    int j = i - 1;
                    do
                    {
                        ans[j] = ans[j] - 1;
                        ans[j + 1] = '9';
                    } while (--j >= 0 && ans[j] > ans[j + 1]);

                    int k = (N.size() - 1) - (i + 1) + 1;
                    while (k--)
                        ans += '9';

                    if (ans[0] == '0')
                        ans = ans.substr(1);

                    break;
                }
            }
        }

        cout << "Case #" << to_string(t) << ": " << ans << endl;
    }
    cin >> T;
}