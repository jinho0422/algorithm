#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[22];
char board[22][22];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool alpa_check[30];
int result;

typedef struct _pos {
	int h, y;
}pos;

void DFS(int depth, int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	alpa_check[board[0][0] - 'A'] = true;
	DFS(1, 0, 0);
	printf("%d\n", result);

	return 0;
}

void DFS(int depth, int hang, int yal) {
	if (result < depth) result = depth;

	for (int dir = 0; dir < 4; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

		if (!alpa_check[board[newY][newX] - 'A']) {
			alpa_check[board[newY][newX] - 'A'] = true;
			DFS(depth + 1, newY, newX);
			alpa_check[board[newY][newX] - 'A'] = false;

		}
	}
}