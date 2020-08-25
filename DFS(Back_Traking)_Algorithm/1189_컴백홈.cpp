#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, K;
char str[7];
char board[7][7];
bool check[7][7];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;

void DFS(int depth, int hang, int yal);

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	//처음 출발하는 왼쪽 아래값을 방문체크..
	check[N - 1][0] = true;
	DFS(0, N - 1, 0);
	check[N - 1][0] = false;

	printf("%d\n", result);
	return 0;
}

void DFS(int depth, int hang, int yal) {
	//움직인 횟수가 처음자리 포함 K번이므로 K -1번째이고 오른쪽 위쪽이면 결과값을 증가..
	if (hang == 0 && yal == M - 1 && depth == K -1) {
		result++;
		return;
	}
	//현재의 점에서 상하좌우를 보고 움직일 수 있는 곳을 판단..
	for (int dir = 0; dir < 4; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

		if (board[newY][newX] == '.' && !check[newY][newX]) {
			check[newY][newX] = true; // 움직일 곳을 방문체크해주고
			DFS(depth + 1, newY, newX); // 재귀..
			check[newY][newX] = false;
		}
	}
}