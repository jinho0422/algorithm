#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;
int board[1001][1001];
int check[2][1001][1001];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt, t;
}pos;
pos start[1];
pos endd[1];

struct cmp {
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);

	for (int a, b, i = 0; i < 2; i++) {
		scanf("%d %d", &a, &b);
		if (i == 0) start[0] = { a, b, 0, 0 };
		else endd[0] = { a, b, 0, 0 };
	}

	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	BFS(start[0].h, start[0].y);

	return 0;
}

void BFS(int hang, int yal) {
	check[0][hang][yal] = true;
	Q.push(pos({ hang, yal, 0, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (p.h == endd[0].h && p.y == endd[0].y) {
			printf("%d\n", p.t);
			return;
		}

		if (p.cnt == 0) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > M) continue;

				if (board[newY][newX] == 0) {
					if (!check[p.cnt][newY][newX]) {
						check[p.cnt][newY][newX] = true;
						Q.push(pos({ newY, newX, p.cnt, p.t + 1 }));
					}
				}

				else if (board[newY][newX] == 1) {
					if (!check[p.cnt + 1][newY][newX]) {
						check[p.cnt + 1][newY][newX] = true;
						Q.push(pos({ newY, newX, p.cnt + 1, p.t + 1 }));
					}
				}
			}
		}

		if (p.cnt == 1) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > M) continue;

				if (board[newY][newX] == 0 && !check[p.cnt][newY][newX]) {
					check[p.cnt][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt, p.t + 1 }));
				}
			}
		}
	}
	printf("-1\n");
}