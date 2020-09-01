#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[101][101];
bool check[101];
int min_sum;
int result;

vector<int> Vec[101];

void BFS(int start);

int main() {
	min_sum = 2147000000;
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		BFS(i);
		memset(check, false, sizeof(check));
	}

	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = 1; j <= M; j++) {
			if (i == j) continue;
			sum += board[i][j];
		}
		if (min_sum > sum) {
			min_sum = sum;
			result = i;
		}
	}
	printf("%d\n", result);
	return 0;
}

void BFS(int start) {
	check[start] = true;
	queue<int> Q;
	Q.push(start);
	int num = 1;

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();

			int Vsz = Vec[p].size();
			for (int ss = 0; ss < Vsz; ss++) {
				int first = Vec[p][ss];
				if (!check[first]) {
					board[start][first] = num;
					check[first] = true;
					Q.push(first);
				}
			}
		}
		num++;
	}
}