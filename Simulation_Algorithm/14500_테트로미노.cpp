#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int board[501][501];
int maxResult;


void check(int hang, int yal);

int main() {
	//입력
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
	// 일자 2개

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

	// 네모 1개

	if (hang + 1 <= N - 1 && yal + 1 <= M - 1) {
		int sum = board[hang][yal] + board[hang][yal + 1] + board[hang + 1][yal] + board[hang + 1][yal + 1];
		if (maxResult < sum) maxResult = sum;
	}

	// 기억 8개

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

	// 격자 4개

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

	// ㅗ자 4개

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
