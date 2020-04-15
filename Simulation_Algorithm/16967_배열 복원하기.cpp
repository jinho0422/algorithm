/*
	https://www.acmicpc.net/problem/13335
	check�迭�� ���� �Ȱ�ġ�� �κ��� false, ��ġ�� �κ��� true�� �Ͽ�
	check�� false�̸� �״�� result_board�� �ְ� 
	check�� true�̸� board[hang][yal] - result_board[hang -X][yal -Y]�Ͽ� 
	�ִ� �˰��� ����.

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
	// ��ġ�� �κ��� ã�� ��
	for (int hang = X; hang < N; hang++) {
		for (int yal = Y; yal < M; yal++) {
			checkB[hang][yal] = true;
		}
	}
	// �Ȱ�ġ�� �κ��� result_board�� �ִ´�
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (!checkB[hang][yal]) {
				result_board[hang][yal] = board[hang][yal];
			}
		}
	}
	// ��ġ�� �κ��� board[hang][yal] - result-board[hang -X][yal - Y]�� �ؼ� �ִ´�.
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