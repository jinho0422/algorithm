#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int board[21][21];
bool check[21][21];
bool tmpCheck[21][21];
int sums[5];
int dirY[4] = { 1, 1, -1, -1 };
int dirX[4] = { 1, -1, -1, 1 };
int result;


typedef struct _pos {
	int h, y;
}pos;
pos turns[4]; // turn되는 곳 넣기..

void DFS(int hang, int yal, int dir, int sum,int fh, int fy);

int main() {
	result = 987654321;
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int hang = 0; hang < N - 2; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (yal == 0 || yal == N - 1) continue;
			DFS(hang, yal, 0, 0, hang, yal);
		}
	}
	printf("%d\n", result);
	return 0;
}
// 각각의 구역 더하기..
void sumCheck() {
	memcpy(tmpCheck, check, sizeof(tmpCheck));
	memset(sums, 0, sizeof(sums));
	for (int hang = 0; hang < turns[2].h; hang++) {
		for (int yal = 0; yal <= turns[3].y; yal++) {
			if (tmpCheck[hang][yal]) break;
			sums[0] += board[hang][yal];
			tmpCheck[hang][yal] = true;
		}
	}
	for (int hang = 0; hang <= turns[0].h; hang++) {
		for (int yal = N - 1; yal > turns[3].y; yal--) {
			if (tmpCheck[hang][yal]) break;
			sums[1] += board[hang][yal];
			tmpCheck[hang][yal] = true;
		}
	}
	for (int hang = N - 1; hang >= turns[2].h; hang--) {
		for (int yal = 0; yal < turns[1].y; yal++) {
			if (tmpCheck[hang][yal]) break;
			sums[2] += board[hang][yal];
			tmpCheck[hang][yal] = true;
		}
	}
	for (int hang = N - 1; hang > turns[0].h; hang--) {
		for (int yal = N - 1; yal >= turns[1].y; yal--) {
			if (tmpCheck[hang][yal]) break;
			sums[3] += board[hang][yal];
			tmpCheck[hang][yal] = true;
		}
	}
}
// 경계값 찾기..
void DFS(int hang, int yal, int dir, int sum, int fh, int fy) {
	if (hang == fh && yal == fy && dir == 3) {
		turns[dir] = { hang, yal };
		sumCheck();
		// 경계값 안에 있는 거 더하기
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if (!tmpCheck[hang][yal]) sums[4] += board[hang][yal];
			}
		}
		sums[4] += sum; // 경계값 더하기..
		sort(sums, sums + 5);
		if (result > sums[4] - sums[0]) result = sums[4] - sums[0];
		return;
	}

	for (int d = 0; d < 2; d++) {
		int newD = dir + d;
		int newY = hang + dirY[newD];
		int newX = yal + dirX[newD];

		if (newY >= 0 && newY <= N - 1 && newX >= 0 && newX <= N - 1) {
			if (newD != dir) turns[dir] = { hang, yal };
			if (!check[newY][newX]) {
				check[newY][newX] = true;
				DFS(newY, newX, newD, sum + board[newY][newX], fh, fy);
				check[newY][newX] = false;
			}
		}
	}
}