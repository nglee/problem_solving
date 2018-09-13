#include <iostream>
#include <vector>

using namespace std;

void solve()
{
	int N;
	int ans;

	cin >> N;

	vector<int> parent(N + 1); // 부모노드가 없으면 0으로 하기 위해 노드 번호는 1~N까지
	vector<bool> isAncestor(N + 1);

    // 트리 구조 입력 받기
	for (int i = 0; i < N - 1; i++) {
		int A, B;
		cin >> A >> B;
		parent[B] = A;
	}

	int c1, c2;
	cin >> c1 >> c2;
	if (parent[c1] == 0) { // c1이 루트노드?
		ans = c1;
	} else if (parent[c2] == 0) { // c2가 루트노드?
		ans = c2;
	} else {
		isAncestor[c1] = true; // 자기자신
		while (parent[c1]) {
			c1 = parent[c1];
			isAncestor[c1] = true; // 조상인 것들을 체크
		}
		isAncestor[c1] = true; // 루트노드

		while (!isAncestor[c2]) // 자기자신부터 확인
			c2 = parent[c2];
		ans = c2;
	}

	cout << ans << "\n";
}

int main()
{
	int T;
	cin >> T;
	while (T--) solve();
}