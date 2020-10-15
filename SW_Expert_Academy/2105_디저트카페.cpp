#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
using namespace std;

int N;
int board[21][21];
int dirY[4] = { 1, 1, -1, -1 };
int dirX[4] = { 1, -1, -1, 1 };
bool check[21][21];
bool desert[101];
int result;

void DFS(int depth, int hang, int yal, int d, int fh, int fy);

int main() {
	freopen("test.txt", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		result = 0;
		memset(board, 0, sizeof(board));
		memset(check, false, sizeof(check));
		memset(check, false, sizeof(check));
		scanf("%d", &N);
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
			}
		}
		for (int hang = 0; hang < N - 2; hang++) {
			for (int yal = 1; yal < N - 1; yal++) {
				DFS(0, hang, yal, 0, hang, yal);
			}
		}
		if (result == 0) printf("#%d -1\n", t);
		else printf("#%d %d\n", t, result);
	}

	return 0;
}

void DFS(int depth, int hang, int yal, int d, int fh, int fy) {
	if (d == 3 && hang == fh && yal == fy) {
		if (result < depth) result = depth;
		//for (int i = 0; i < N; i++) {
		//	for (int j = 0; j < N; j++) {
		//		printf("%d ", check[i][j]);
		//	}
		//	printf("\n");
		//}
		return;
	}

	for (int dir = 0; dir < 2; dir++) {
		int newD = d + dir;
		int newY = hang + dirY[newD];
		int newX = yal + dirX[newD];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

		if (!check[newY][newX]) {
			if (!desert[board[hang][yal]]) {
				check[newY][newX] = true;
				desert[board[hang][yal]] = true;
				if (newD != d) d++;
				DFS(depth + 1, newY, newX, d, fh, fy);
				if (newD != d) d--;
				check[newY][newX] = false;
				desert[board[hang][yal]] = false;
			}
		}
	}
}