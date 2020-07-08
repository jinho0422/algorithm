#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
// ������ ���� ����� check�ϴ� �迭
bool check[102];
// ������ �ϴ� ������κ��� �޴� ����� �ִ� vector
vector<int> Vec[102];
// ������ �����ñ⿡ ������ �޴� ����ǹ�ȣ�� �ִ� queue
queue<int> Q;

int BFS(int start);

int main() {
	//freopen("test.txt", "r", stdin);
	//�Է�
	for (int t = 1; t <= 10; t++) {
		scanf("%d %d", &N, &M);

		for (int a, b, i = 0; i < N; i+=2) {
			scanf("%d %d", &a, &b);
			Vec[a].push_back(b);
		}
		// BFS�� ���� ó�� ������ ���ϴ� ������κ��� ������ ������ �޴� ������� ã�´�.
		int max_result = BFS(M);
		//���
		printf("#%d %d\n", t, max_result);
		//�ʱ�ȭ
		memset(check, false, sizeof(check));
		for (int i = 0; i < 102; i++) Vec[i].clear();
		while (!Q.empty()) Q.pop();
	}
	return 0;
}

int BFS(int start) {
	check[start] = true;
	Q.push(start);
	int result = 0;
	while (!Q.empty()) {
		result = 0;
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			// ������ ���� �ñ⿡ ������κ��� �ִ��� ��ȣ�� �̾Ƴ���..
			if (result < p) result = p;

			//������ �ϴ� ������κ��� �޴� ����� �����ʾҴ� ����̸� ������ �ϸ鼭 queue�� �ִ´�.
			int vecSz = Vec[p].size();
			for (int i = 0; i < vecSz; i++) {
				int arrive = Vec[p][i];
				if (!check[arrive]) {
					check[arrive] = true;
					Q.push(arrive);
				}
			}
		}
	}
	return result;
}