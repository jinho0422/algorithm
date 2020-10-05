#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[51][51];
int dirY[4] = { 0, 1, 0, -1 }; // 방향을 우, 하, 좌, 상 으로 하는 것이 시간을 줄이는데 효과적이다.
int dirX[4] = { 1, 0, -1, 0 };
bool flag;

void DFS(int depth, int hang, int yal, int fh, int fy);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	for (int hang = 0; hang < N -1; hang++) {
		for (int yal = 0; yal < M -1; yal++) {
			DFS(1, hang, yal, hang, yal); // 연결된 것이 몇개인지, 시작 hang, yal, 연결이 되었느지 판단하기 위한 hang, yal
			//연결되었으면
			if (flag) {
				printf("Yes\n");
				return 0;
			}
		}
	}
	//하나라도 만족하는 값이 없으면..
	printf("No\n");
	return 0;
}

void DFS(int depth, int hang, int yal, int fh, int fy) {
	if (flag) return;
	if (depth >= 4 && hang == fh && yal == fy) {
		flag = true;
		return;
	}
	for (int dir = 0; dir < 4; dir++) {
		
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 ) continue;

		if (!check[newY][newX] && board[newY][newX] == board[fh][fy]) {
			check[newY][newX] = true;
			DFS(depth + 1, newY, newX, fh, fy);
			check[newY][newX] = false;
		}
	}
}