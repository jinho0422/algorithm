/*
	https://www.acmicpc.net/problem/13335
	check배열을 통해 안겹치는 부분은 false, 겹치는 부분은 true로 하여
	check가 false이면 그대로 result_board에 넣고 
	check가 true이면 board[hang][yal] - result_board[hang -X][yal -Y]하여 
	넣는 알고리즘 구현.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, X, Y;
int board[603][603];
bool checkB[603][603];
int result_board[303][303];

int main() {
	scanf("%d %d %d %d", &N, &M, &X, &Y);
	for (int hang = 0; hang < N + X; hang++) {
		for (int yal = 0; yal < M + Y; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// 겹치는 부분을 찾는 곳
	for (int hang = X; hang < N; hang++) {
		for (int yal = Y; yal < M; yal++) {
			checkB[hang][yal] = true;
		}
	}
	// 안겹치는 부분을 result_board에 넣는다
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (!checkB[hang][yal]) {
				result_board[hang][yal] = board[hang][yal];
			}
		}
	}
	// 겹치는 부분은 board[hang][yal] - result-board[hang -X][yal - Y]를 해서 넣는다.
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (checkB[hang][yal]) result_board[hang][yal] = board[hang][yal] - result_board[hang - X][yal - Y];
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			printf("%d ", result_board[hang][yal]);
		}
		printf("\n");
	}

	return 0;
}