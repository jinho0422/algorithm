/*
	https://www.acmicpc.net/problem/10836
	M초까지 board[hang-1][0]부터 board[1][0]까지 board[0][0]부터 board[0][yal -1] 까지
	증가값을 numbers배열에 넣어 각각을 대입하고 board[1][1] 부터 board[N -1][N -1]까지
	왼쪽, 위쪽, 왼쪽위에서 max값을 찾아 대입하는 알고리즘 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N, M;
int board[701][701];
int numbers[1501]; //M초까지 board[hang-1][0]부터 board[1][0]까지 board[0][0]부터 board[0][yal -1] 까지 증가값을 넣는 배열..
 
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < 2 * N - 1; i++) numbers[i] = 1; // 1로 초기화..

	for (int a, b, c, i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c); // 0++ 1++ 2++가 몇개 있는지 보고
		int num = a; // 0++는 결과값에 영향을 미치지 않으므로 num 초기값을 a로 설정
		for (int j = 0; j < b; j++) { // numbers배열을 통해  b까지 1++를 대입하고
			numbers[num++] += 1;
		}
		for (int j = 0; j < c; j++) {// numbers배열을 통해 c까지 2++를 대입하고
			numbers[num++] += 2;
		}
	}
	int cnt = 0; // board배열에 가장 왼쪽아래부터 가장 왼쪽위까지 가장 위쪽 왼쪽부터 가장 위쪽 오른쪽까지 numbers배열의 값을 대입
	for (int hang = N - 1; hang > 0; hang--) {
		board[hang][0] = numbers[cnt++];
	}
	for (int yal = 0; yal < N; yal++) {
		board[0][yal] = numbers[cnt++];
	}

	// board[1][1]부터 board[N -1][N -1] 값까지 왼쪽 위쪽 왼쪽위의 값의 최대값을 board값에 대입.
	for (int hang = 1; hang < N; hang++) {
		for (int yal = 1; yal < N; yal++) {
			int up_max = max(board[hang - 1][yal - 1], board[hang - 1][yal]);
			board[hang][yal] = max(up_max, board[hang][yal - 1]);
		}
	}
	//결과값 출력
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			printf("%d ", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}