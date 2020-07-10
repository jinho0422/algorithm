#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
int board[1002][1002];
int dp[1002][1002];
int result;


int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			if (board[hang][yal] == 0) {
				dp[hang][yal] = min(min(dp[hang - 1][yal], dp[hang][yal - 1]), dp[hang - 1][yal - 1]) + 1;
				result = max(result, dp[hang][yal]);
			}
		}
	}
	printf("%d\n", result);

	return 0;
}
