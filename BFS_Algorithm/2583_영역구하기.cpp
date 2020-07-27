#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, K;
int board[101][101];
bool check[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

queue<pos> Q;
vector<int> Vec;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int sy, sh, fy, fh, i = 0; i < K; i++) {
		scanf("%d %d %d %d", &sy, &sh, &fy, &fh);
		for (int hang = sh; hang < fh; hang++) {
			for (int yal = sy; yal < fy; yal++) {
				board[hang][yal] = 1;
			}
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0 && !check[hang][yal]) {
				BFS(hang, yal);
			}
		}
	}

	sort(Vec.begin(), Vec.end());
	int sz = Vec.size();
	printf("%d\n", sz);
	for (int s = 0; s < sz; s++) {
		printf("%d ", Vec[s]);
	}
	printf("\n");

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	int area = 1;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				area++;
				Q.push(pos({ newY, newX }));
			}
		}
	}
	Vec.push_back(area);
}