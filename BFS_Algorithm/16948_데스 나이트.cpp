#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;
int sh, sy, fh, fy;
bool check[201][201];
int dirY[6] = { -2, -2, 0, 0, 2, 2 };
int dirX[6] = { -1, 1, -2, 2, -1, 1 };

typedef struct _pos {
	int h, y;
}pos;

void BFS(int hang, int yal);

int main() {
	scanf("%d", &N);
	scanf("%d %d %d %d", &sh, &sy, &fh, &fy);
	
	BFS(sh, sy);
	return 0;
}

void BFS(int hang, int yal) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			if (p.h == fh && p.y == fy) {
				printf("%d\n", time);
				return;
			}

			for (int dir = 0; dir < 6; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (!check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
			}
		}
		time++;
	}
	printf("-1\n");
}