#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[105][105];
bool check[105][105];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int island;
int min_result;

typedef struct _pos {
	int h, y;
}pos;

queue<pos> Q;

void BFS(int hang, int yal);
int BFS1(int hang, int yal);

int main() {
	min_result = 2147000000;
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	island = 1;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal);
				island++;
			}
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (board[hang][yal] != 0) {
				for (int dir = 0; dir < 4; dir++) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];

					if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

					if (board[newY][newX] == 0) {
						memset(check, false, sizeof(check));
						while (!Q.empty()) Q.pop();
						int result = BFS1(hang, yal);
						if (min_result > result) min_result = result;
						break;
					}
				}
			}
		}
	}
	printf("%d\n", min_result);
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	board[hang][yal] = island;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = island;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}

int BFS1(int hang, int yal) {
	check[hang][yal] = true;
	int cnt = 0;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {	
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (board[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
				if (board[newY][newX] != 0 && board[newY][newX] != board[hang][yal]) {
					return cnt;
				}
			}
		}
		cnt++;
		if (min_result <= cnt) return cnt;
	}
}