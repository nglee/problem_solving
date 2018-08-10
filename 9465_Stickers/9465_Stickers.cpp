#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int top[100000];

void solve()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) scanf("%d", &top[i]);

	pair<int, int> dyn[3];
	dyn[0].first = top[0];
	scanf("%d", &dyn[0].second);
	dyn[1].first = top[1] + dyn[0].second;
	scanf("%d", &dyn[1].second);
	dyn[1].second += dyn[0].first;
	for (int i = 2; i < N; i++) {
		int idx = i % 3;
		int idx_1 = (i - 1) % 3;
		int idx_2 = (i - 2) % 3;
		dyn[idx].first = top[i] + max(dyn[idx_1].second, dyn[idx_2].second);
	    scanf("%d", &dyn[idx].second);
		dyn[idx].second += max(dyn[idx_1].first, dyn[idx_2].first);
	}
	int idx_ans = (N - 1) % 3;
	printf("%d\n", max(dyn[idx_ans].first, dyn[idx_ans].second));
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}


//typedef int TopBest;
//typedef int BotBest;
//
//void solve()
//{
//	int N;
//	cin >> N;
//
//	vector<int> top(N), bot(N);
//	for (int i = 0; i < N; i++) cin >> top[i];
//	for (int i = 0; i < N; i++) cin >> bot[i];
//
//	vector<pair<TopBest, BotBest>> dyn(N);
//	dyn[N - 1].first = top[N - 1];
//	dyn[N - 1].second = bot[N - 1];
//	dyn[N - 2].first = top[N - 2] + dyn[N - 1].second;
//	dyn[N - 2].second = bot[N - 2] + dyn[N - 1].first;
//	for (int i = N - 3; i >= 0; i--) {
//		dyn[i].first = top[i] + max(dyn[i + 1].second, dyn[i + 2].second);
//		dyn[i].second = bot[i] + max(dyn[i + 1].first, dyn[i + 2].first);
//	}
//	cout << max(dyn[0].first, dyn[0].second) << endl;
//}
//
//int main()
//{
//	int T;
//	cin >> T;
//	while (T--)
//		solve();
//	cin >> T;
//}