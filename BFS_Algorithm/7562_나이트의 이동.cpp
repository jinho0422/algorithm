#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N;
int sh, sy, fh, fy;
int check[301][301];
int dirY[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dirX[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

typedef struct _pos {
	int h, y;
}pos;

void BFS(int hang, int yal);

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		scanf("%d %d %d %d", &sh, &sy, &fh, &fy);
		BFS(sh, sy);
		memset(check, false, sizeof(check));
	}

	return 0;
}

void BFS(int hang, int yal) {
	int result_time = 0;
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			if (p.h == fh && p.y == fy) {
				printf("%d\n", result_time);
				return;
			}


			for (int dir = 0; dir < 8; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (!check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
			}
		}
		result_time++;
	}
}