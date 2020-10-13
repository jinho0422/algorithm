#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, sh, sy, K;
int board[21][21];
int dirY[5] = { 0, 0, 0, -1, 1 };
int dirX[5] = { 0, 1, -1, 0, 0 };
int dice[7];
int wall;

void turns(int a, int b, int c, int d);

int main() {
	//입력
	scanf("%d %d %d %d %d", &N, &M, &sh, &sy, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// 1:bottom, 2:back, 3:right, 4:left, 5: front, 6:top   
	for (int a, i = 0; i < K; i++) {
		scanf("%d", &a);
		int newY = sh + dirY[a];
		int newX = sy + dirX[a];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
		// 주사위 이동방향
		if (a == 1) turns(1, 4, 6, 3);	// 1--> 4 --> 6 --> 3 --> 1
		else if (a == 2) turns(1, 3, 6, 4);	
		else if (a == 3) turns(1, 5, 6, 2);	
		else turns(1, 2, 6, 5);
		//board가 0이면 주사위의 바닥을 board에 칠한다..
		if (board[newY][newX] == 0) board[newY][newX] = dice[1];
		// board가 0이 아니면 board를 주사위 바닥에 칠한다.
		else {
			dice[1] = board[newY][newX];
			board[newY][newX] = 0;
		}
		// 주사위 위치 갱신 & 출력
		sh = newY, sy = newX;
		printf("%d\n", dice[6]);
	}
	return 0;
}
// 주사위 굴리기
void turns(int a, int b, int c, int d) {
	int tmp = dice[a];
	dice[a] = dice[d], dice[d] = dice[c], dice[c] = dice[b];
	dice[b] = tmp;
}