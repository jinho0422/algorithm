#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int T, N;
bool check[102];
bool flag;

vector<int> Vec[102];
queue<int> Q;

void BFS(int start);

int main() {
	//freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		//�������� �����ߴ����� �Ǵ��� flag �ʱ�ȭ, �Է�..Vec ������ �� �� �ִ� ������ ����..
		flag = false;
		scanf("%d %d", &T, &N);
		for (int a, b, s = 0; s < N; s++) {
			scanf("%d %d", &a, &b);
			Vec[a].push_back(b);
		}
		//BFS�� ���� �� �� �ִ� ���� visited�ϸ鼭 ���������� �������� �Ǵ�..
		BFS(0);
		//���..
		if (flag) printf("#%d 1\n", t);
		else printf("#%d 0\n", t);
		//�ʱ�ȭ..
		for (int s = 0; s < 100; s++) Vec[s].clear();
		while (!Q.empty()) Q.pop();
		memset(check, false, sizeof(check));
	}

	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		//�������� �����ϸ� flag�� �������� �����ߴٴ� ǥ�ø� �ϰ� �Լ��� �������´�.
		if (p == 99) {
			flag = true;
			return;
		}

		for (int s = 0; s < Vec[p].size(); s++) {
			if (!check[Vec[p][s]]) {
				check[Vec[p][s]] = true;
				Q.push(Vec[p][s]);
			}
		}
	}

}