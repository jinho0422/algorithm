#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[301][301];
bool check[301][301];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int NoZero;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] != 0) NoZero++;
			else if (board[hang][yal] == 0) Vec.push_back(pos({ hang, yal }));
		}
	}
	int time = 0;
	while (1) {

		if (NoZero == 0) {
			printf("0\n");
			break;
		}
		int cnt = 0;
		memset(check, false, sizeof(check));
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (board[hang][yal] != 0 && !check[hang][yal]) {
					BFS(hang, yal);
					cnt++;
				}
			}
		}
		if (cnt > 1) {
			printf("%d\n", time);
			break;
		}

		int sz = Vec.size();
		for (int s = 0; s < sz; s++) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[s].h + dirY[dir];
				int newX = Vec[s].y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] != 0) {
					board[newY][newX] -= 1;
					if (board[newY][newX] == 0) {
						Vec.push_back(pos({ newY, newX }));
						NoZero--;
					}
				}
			}
		}
		time++;
	}

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] != 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}