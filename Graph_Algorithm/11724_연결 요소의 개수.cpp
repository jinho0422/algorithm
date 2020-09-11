#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int N, M;
bool check[1001];

vector<int> Vec[1001];

void BFS(int start);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b); // ������ ���⶧����
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}
	int result = 0; // �����
	for (int i = 1; i <= N; i++) { // 1~ N ���� ���鼭 ���� �湮�� ���� �ʾҴٸ� �� �κк��� �� ���ִ� ������ ��� �湮ó���Ѵ�.
		if (!check[i]) {
			BFS(i);
			result++;
		}
	}
	//���
	printf("%d\n", result);
	return 0;
}

void BFS(int start) {
	check[start] = true;
	queue<int> Q;
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];
			if (!check[first]) {
				check[first] = true; // �湮���� �ʾҴٸ� �湮
				Q.push(first);
			}
		}
	}
}