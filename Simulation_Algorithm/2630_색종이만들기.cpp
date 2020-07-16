#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
using namespace std;

int N;
int board[135][135];
bool check[135][135];
int checkCnt[2];
int result[2];

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// checkPoint == 변의 길이를 반으로 나누기위해.. breakCnt == 색종이로 채택된 부분의 갯수를 빼서 while문을 빠져나오기위해
	int checkPoint = N, breakCnt = N * N;
	// startH == while의 for문 행의 start 지점, startY == 열의 start 지점
	int startH = 0, startY = 0;
	while (1) {
		for (int i = startH; i < startH + checkPoint; i++) {
			for (int j = startY; j < startY + checkPoint; j++) {
				if (check[i][j]) continue;
				if (board[i][j] == 0) checkCnt[0]++;
				else checkCnt[1]++;
			}
		}
		//만약 for문을 돌고 checkCnt의 값이 변 가로 세로의 곱이랑 같으면 색종이로 인정..
		if (checkCnt[0] == checkPoint * checkPoint) {
			result[0]++;
			for (int i = startH; i < startH + checkPoint; i++) {
				for (int j = startY; j < startY + checkPoint; j++) {
					check[i][j] = true;
				}
			}
			breakCnt -= checkPoint * checkPoint;
		}
		if (checkCnt[1] == checkPoint * checkPoint) {
			result[1]++;
			for (int i = startH; i < startH + checkPoint; i++) {
				for (int j = startY; j < startY + checkPoint; j++) {
					check[i][j] = true;
				}
			}
			breakCnt -= checkPoint * checkPoint;
		}
		// 색종이인지를 판단하는 checkCnt 초기화..
		memset(checkCnt, 0, sizeof(checkCnt));

		// 정사각형을 모두 돌았으면 변을 반으로 나눠서 다시돈다..
		if (startH + checkPoint == N && startY + checkPoint == N) {
			checkPoint /= 2;
			startH = 0, startY = 0;
		}
		// 아직 정사각형을 다 돌지 않았으면 열이 N(처음 정사각형의 길이)와 같으면 행을 checkPoint를 더해주고 시작한다.
		else {
			if (startY + checkPoint == N) {
				startH += checkPoint;
				startY = 0;
			}
			else startY += checkPoint;
		}
		// 변의 길이를 반으로나누면서 다 돌았거나 모든 곳이 색종이로 쓸수있는 곳이면 break..
		if (checkPoint == 0 || breakCnt == 0) break;
	}
	//출력
	for (int i = 0; i < 2; i++) printf("%d\n", result[i]);
	return 0;
}