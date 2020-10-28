#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int board[501][501];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int dp[501][501];
int result;

int DFS(int hang, int yal);

int main() {
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			dp[hang][yal] = -1;
		}
	}
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			result = max(result, DFS(hang, yal));
			printf("%d %d\n", hang, yal);
			for (int hang = 0; hang < N; hang++) {
				for (int yal = 0; yal < N; yal++) {
					printf("%d ", dp[hang][yal]);
				}
				printf("\n");
			}
		}
	}
	printf("%d\n", result);
	return 0;
}

int DFS(int hang, int yal) {

	if (dp[hang][yal] == -1) {
		dp[hang][yal] = 1;
		int tmp = 0;
		for (int dir = 0; dir < 4; dir++) {
			int newY = hang + dirY[dir];
			int newX = yal + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[hang][yal] > board[newY][newX]) continue;
			tmp = max(tmp, DFS(newY, newX));
		}
		dp[hang][yal] += tmp;
	}
	return dp[hang][yal];
}