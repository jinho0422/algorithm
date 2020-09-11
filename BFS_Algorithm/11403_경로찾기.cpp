#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[101][101];
bool check[101];

vector<int> Vec[101];

void BFS(int start);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) { // ���� hang(i)���� yal(j)�� ���� ���� �����Ƿ� vector�� �ִ´�.
				Vec[hang].push_back(yal);
			}
		}
	}
	for (int i = 0; i < N; i++) { // 0���� N -1���� �ϳ��� �������� �� �� �ִ� ���� BFS�� ���� �̵��Ѵ�..
		BFS(i);
		memset(check, false, sizeof(check));// �ʱ�ȭ
	}
	//���
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			printf("%d ", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}

void BFS(int start) {
	queue<int> Q;
	Q.push(start);
	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];

			if (!check[first]) {
				check[first] = true;
				Q.push(first);
				board[start][first] = 1;
			}
		}
	}
}