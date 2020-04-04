/*
	https://www.acmicpc.net/problem/14500
	5���� ����� ����, ȸ���� ���� ���� �� �ִ� ����� �� 18�� 
	�ϵ��ڵ��� ���� 18���� ����� hang, yal�� ���鼭 �ִ��� ���� �����ϴ� �˰��� ����.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N, M;
int board[500][500];


int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	int result = 0;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			//����(2)
			if (yal + 3 < M) {
				result = max(result, board[hang][yal] + board[hang][yal + 1] + board[hang][yal + 2] + board[hang][yal + 3]);
			}
			if (hang + 3 < N) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 2][yal] + board[hang + 3][yal]);
			}
			//�׸�(1)
			if (hang + 1 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang][yal + 1] + board[hang + 1][yal + 1]);
			}
			//���(4)
			if (hang + 2 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 1][yal + 1] + board[hang + 2][yal + 1]);
			}
			if (hang + 1 < N && yal + 2 < M) {
				result = max(result, board[hang][yal] + board[hang][yal + 1] + board[hang + 1][yal + 1] + board[hang + 1][yal + 2]);
			}
			if (hang + 2 < N && yal - 1 >= 0) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 1][yal - 1] + board[hang + 2][yal - 1]);
			}
			if (hang + 1 < N && yal - 2 >= 0) {
				result = max(result, board[hang][yal] + board[hang][yal - 1] + board[hang + 1][yal - 1] + board[hang + 1][yal - 2]);
			}
			//��(4)
			if (hang + 1 < N && yal + 1 < M && yal - 1 >= 0) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 1][yal - 1] + board[hang + 1][yal + 1]);
			}
			if (hang - 1 >= 0 && hang + 1 < N && yal - 1 >= 0) {
				result = max(result, board[hang][yal] + board[hang][yal - 1] + board[hang - 1][yal - 1] + board[hang + 1][yal -1]);
			}
			if (hang - 1 >= 0 && hang + 1 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang - 1][yal + 1] + board[hang][yal + 1] + board[hang + 1][yal + 1]);
			}
			if (hang - 1 >= 0 && yal - 1 >= 0 && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang - 1][yal] + board[hang - 1][yal - 1] + board[hang - 1][yal + 1]);
			}
			//��(8)
			if (hang + 2 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang][yal + 1] + board[hang + 1][yal + 1] + board[hang + 2][yal + 1]);
			}
			if (hang + 2 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang][yal + 1] + board[hang + 1][yal] + board[hang + 2][yal]);
			}
			if (hang + 1 < N && yal - 2 >= 0) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 1][yal -1] + board[hang + 1][yal -2]);
			}
			if (hang + 2 < N && yal + 1 < M) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 2][yal] + board[hang + 2][yal + 1]);
			}
			if (hang + 1 < N && yal + 2 < M) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang][yal + 1] + board[hang][yal + 2]);
			}
			if (hang + 1 < N && yal + 2 < M) {
				result = max(result, board[hang][yal] + board[hang][yal + 1] + board[hang][yal + 2] + board[hang + 1][yal + 2]);
			}
			if (hang + 1 < N && yal + 2 < M) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 1][yal + 1] + board[hang + 1][yal + 2]);
			}
			if (hang + 2 < N && yal -1 >= 0) {
				result = max(result, board[hang][yal] + board[hang + 1][yal] + board[hang + 2][yal] + board[hang + 2][yal - 1]);
			}
		}
	}
	printf("%d\n", result);

	return 0;
}