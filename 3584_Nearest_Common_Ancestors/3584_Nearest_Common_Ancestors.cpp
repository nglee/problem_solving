#include <iostream>
#include <vector>

using namespace std;

void solve()
{
	int N;
	int ans;

	cin >> N;

	vector<int> parent(N + 1); // �θ��尡 ������ 0���� �ϱ� ���� ��� ��ȣ�� 1~N����
	vector<bool> isAncestor(N + 1);

    // Ʈ�� ���� �Է� �ޱ�
	for (int i = 0; i < N - 1; i++) {
		int A, B;
		cin >> A >> B;
		parent[B] = A;
	}

	int c1, c2;
	cin >> c1 >> c2;
	if (parent[c1] == 0) { // c1�� ��Ʈ���?
		ans = c1;
	} else if (parent[c2] == 0) { // c2�� ��Ʈ���?
		ans = c2;
	} else {
		isAncestor[c1] = true; // �ڱ��ڽ�
		while (parent[c1]) {
			c1 = parent[c1];
			isAncestor[c1] = true; // ������ �͵��� üũ
		}
		isAncestor[c1] = true; // ��Ʈ���

		while (!isAncestor[c2]) // �ڱ��ڽź��� Ȯ��
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