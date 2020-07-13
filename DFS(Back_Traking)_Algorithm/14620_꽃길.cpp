#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int board[11][11];
bool check[11][11];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int minResult;

typedef struct _pos {
	int h, y;
}pos;

pos flowers[101];
int num;

void DFS(int depth, int start, int sum);

int main() {
	minResult = 2147000000;
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);

			if (hang > 0 && hang < N - 1 && yal > 0 && yal < N - 1) {
				flowers[num++] = { hang, yal };
			}
		}
	}
	DFS(0, 0, 0);
	printf("%d\n", minResult);
	return 0;
}

bool checkFlowers(int hang, int yal) {
	for (int dir = 0; dir < 4; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (check[newY][newX]) return true;
	}
	return false;
}

void DFS(int depth, int start, int sum) {
	if (minResult < sum) return;

	if (depth == 3) {
		if (minResult > sum) minResult = sum;
		return;
	}
	for (int i = start; i < num; i++) {
		if (!check[flowers[i].h][flowers[i].y]) {
			bool flag = checkFlowers(flowers[i].h, flowers[i].y);
			if (!flag) {
				check[flowers[i].h][flowers[i].y] = true;
				sum += board[flowers[i].h][flowers[i].y];
				for (int dir = 0; dir < 4; dir++) {
					int newY = flowers[i].h + dirY[dir];
					int newX = flowers[i].y + dirX[dir];
					check[newY][newX] = true;
					sum += board[newY][newX];
				}
				DFS(depth + 1, i + 1, sum);
				check[flowers[i].h][flowers[i].y] = false;
				sum -= board[flowers[i].h][flowers[i].y];
				for (int dir = 0; dir < 4; dir++) {
					int newY = flowers[i].h + dirY[dir];
					int newX = flowers[i].y + dirX[dir];
					check[newY][newX] = false;
					sum -= board[newY][newX];
				}
			}
		}
	}
}