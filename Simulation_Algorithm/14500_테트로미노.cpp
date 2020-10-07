#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int board[501][501];
int maxResult;


void check(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			check(hang, yal);
		}
	}
	printf("%d\n", maxResult);
	return 0;
}

void check(int hang, int yal) {
	// ���� 2��

	if (yal + 3 <= M - 1) {
		int sum = 0;
		for (int dir = 0; dir < 4; dir++) {
			sum += board[hang][yal + dir];
		}
		if (maxResult < sum) maxResult = sum;
	}
	if (hang + 3 <= N - 1) {
		int sum = 0;
		for (int dir = 0; dir < 4; dir++) {
			sum += board[hang + dir][yal];
		}
		if (maxResult < sum) maxResult = sum;
	}

	// �׸� 1��

	if (hang + 1 <= N - 1 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal + 1] + board[hang + 1][yal] + board[hang + 1][yal + 1];
		if (maxResult < sum) maxResult = sum;
	}

	// ��� 8��

	if (hang - 2 >= 0 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang - 1][yal] + board[hang - 2][yal] + board[hang][yal + 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && yal + 2 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal + 1] + board[hang][yal + 2] + board[hang - 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang + 2 <= N - 1 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang + 1][yal] + board[hang + 2][yal] + board[hang][yal + 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang + 1 <= N - 1 && yal - 2 >= 0) {
		int sum = board[hang][yal] + board[hang][yal - 1] + board[hang][yal - 2] + board[hang + 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 2 >= 0 && yal - 1 >= 0) {
		int sum = board[hang][yal] + board[hang - 1][yal] + board[hang - 2][yal] + board[hang][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && yal - 2 >= 0) {
		int sum = board[hang][yal] + board[hang][yal - 1] + board[hang][yal - 2] + board[hang - 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang + 2 <= N - 1 && yal - 1 >= 0) {
		int sum = board[hang][yal] + board[hang + 1][yal] + board[hang + 2][yal] + board[hang][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang + 1 <= N - 1 && yal + 2 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal + 1] + board[hang][yal + 2] + board[hang + 1][yal];
		if (maxResult < sum) maxResult = sum;
	}

	// ���� 4��

	if (hang - 1 >= 0 && yal - 1 >= 0 && hang + 1 <= N - 1) {
		int sum = board[hang][yal] + board[hang - 1][yal - 1] + board[hang][yal - 1] + board[hang + 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && yal + 1 <= M - 1 && yal - 1 >= 0) {
		int sum = board[hang][yal] + board[hang - 1][yal + 1] + board[hang - 1][yal] + board[hang][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && hang + 1 <= N - 1 && yal - 1 >= 0) {
		int sum = board[hang][yal] + board[hang - 1][yal] + board[hang][yal - 1] + board[hang + 1][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && yal - 1 >= 0 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal + 1] + board[hang - 1][yal] + board[hang - 1][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}

	// ���� 4��

	if (hang + 1 <= N - 1 && yal - 1 >= 0 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal - 1] + board[hang][yal + 1] + board[hang + 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && hang + 1 <= N - 1 && yal - 1 >= 0) {
		int sum = board[hang][yal] + board[hang - 1][yal] + board[hang + 1][yal] + board[hang][yal - 1];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && yal - 1 >= 0 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal - 1] + board[hang][yal + 1] + board[hang - 1][yal];
		if (maxResult < sum) maxResult = sum;
	}
	if (hang - 1 >= 0 && hang + 1 <= N - 1 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang - 1][yal] + board[hang + 1][yal] + board[hang][yal + 1];
		if (maxResult < sum) maxResult = sum;
	}

}
