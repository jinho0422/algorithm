#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
int board[1001][1001];
int dp[1001][1001];
int dirY[3] = { 1, 0, 1 };
int dirX[3] = { 0, 1, 1 };



void BFS(int hang, int yal, int cnt);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 1; hang <= N; hang++) {
		for(int yal = 1; yal <= M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// (1, 1)���� ���ʴ밢�� ����, ����, ���ʿ����� �ְ��� ���� (1, 1)�� board�� ���� ���� dp �迭�� �ִ´�..
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			dp[hang][yal] = max(dp[hang - 1][yal], max(dp[hang][yal - 1], dp[hang - 1][yal - 1])) + board[hang][yal];
			// ���� �İ� ������ ���̴�
			/*if (dp[hang - 1][yal] + board[hang][yal] > dp[hang][yal]) dp[hang][yal] = dp[hang - 1][yal] + board[hang][yal];
			if (dp[hang][yal - 1] + board[hang][yal] > dp[hang][yal]) dp[hang][yal] = dp[hang][yal - 1] + board[hang][yal];
			if (dp[hang - 1][yal - 1] + board[hang][yal] > dp[hang][yal]) dp[hang][yal] = dp[hang - 1][yal - 1] + board[hang][yal];*/
			
		}
	}
	printf("%d\n", dp[N][M]);
}
