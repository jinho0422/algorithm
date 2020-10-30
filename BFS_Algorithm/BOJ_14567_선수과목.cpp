#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int board[1001];

typedef struct _pos {
	int n, c;
}pos;
queue<pos> Q;
vector<int> Vec[1001];


void BFS(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) board[i] = 1;
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
	}
	for (int i = 1; i <= N; i++) {
		if (Vec[i].size() != 0) BFS(i);
	}

	for (int i = 1; i <= N; i++) {
		printf("%d ", board[i]);
	}
	printf("\n");
	return 0;
}

void BFS(int start) {
	Q.push(pos({ start, 1 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		int sz = Vec[p.n].size();
		for (int s = 0; s < sz; s++) {
			if (board[Vec[p.n][s]] < p.c + 1) {
				board[Vec[p.n][s]] = p.c + 1;
				Q.push(pos({ Vec[p.n][s], p.c + 1 }));
			}
		}
	}
}