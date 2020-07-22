#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[51][51];
bool check[51][51];
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, 1, 0, -1 };
int RH, RY, RD;

typedef struct _pos {
	int h, y, d, cnt;
}pos;

void BFS(int hang, int yal, int D);

int main() {
	scanf("%d %d %d %d %d", &N, &M, &RH, &RY, &RD);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) check[hang][yal] = true;
		}
	}
	BFS(RH, RY, RD);

	return 0;
}


void BFS(int hang, int yal, int D) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal, D, 0 }));
	int cleans = 1;
	
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		if (p.cnt == 4) {
			int new_D = 0;
			if (p.d == 0) new_D = 2;
			else if (p.d == 1) new_D = 3;
			else if (p.d == 2) new_D = 0;
			else if (p.d == 3) new_D = 1;

			int new_Y = p.h + dirY[new_D];
			int new_X = p.y + dirX[new_D];

			if (new_Y < 0 || new_Y > N - 1 || new_X < 0 || new_X > M - 1 || board[new_Y][new_X] == 1) break;
			else {
				if (!check[new_Y][new_X]) {
					check[new_Y][new_X] = true;
					cleans++;
				}
				Q.push(pos({ new_Y, new_X, p.d }));
				continue;
			}
		}
		
		int newD = 0;
		if (p.d == 0) newD = 3;
		else newD = p.d - 1;

		int newY = p.h + dirY[newD];
		int newX = p.y + dirX[newD];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

		if (!check[newY][newX]) {
			check[newY][newX] = true;
			cleans++;
			Q.push(pos({ newY, newX, newD, 0 }));
		}
		else {
			Q.push(pos({ p.h, p.y, newD, p.cnt + 1 }));
		}

	}
	printf("%d\n", cleans);
}