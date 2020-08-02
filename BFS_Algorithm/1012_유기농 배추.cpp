#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>


using namespace std;

int N, M, K;
int board[51][51];
bool check[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

queue<pos> Q;

void BFS(int hang, int yal);

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %d", &N, &M, &K);
		for (int a, b, i = 0; i < K; i++) {
			scanf("%d %d", &a, &b);
			board[a][b] = 1;
		}

		int result = 0;

		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (board[hang][yal] == 1 && !check[hang][yal]) {
					BFS(hang, yal);
					result++;
				}
			}
		}
		printf("%d\n", result);
		memset(check, false, sizeof(check));
		memset(board, 0, sizeof(board));
	}

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}