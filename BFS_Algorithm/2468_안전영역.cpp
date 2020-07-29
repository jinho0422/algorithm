#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[100][100];
bool check[100][100];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int max_H;
int result;

typedef struct _pos {
	int h, y;
}pos;

queue<pos> Q;

void BFS(int hang, int yal, int height);

int main() {
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (max_H < board[hang][yal]) max_H = board[hang][yal];
		}
	}

	for (int i = 0; i < max_H; i++) {
		int count = 0;
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if (board[hang][yal] > i && !check[hang][yal]) {
					BFS(hang, yal, i);
					count++;
				}
			}
		}
		if (result < count) result = count;
		memset(check, false, sizeof(check));
	}
	printf("%d\n", result);

	return 0;
}

void BFS(int hang, int yal, int height) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (board[newY][newX] > height && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}