#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[12];
char board[12][12];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool check[12][12];

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	// 땅일 때 바다에 인접한 면이 몇개인지 찾기..
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 'X') {
				int cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];

					if ((newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '.') && !check[newY][newX]) cnt++;

				}
				if (cnt >= 3) {
					check[hang][yal] = true;
					board[hang][yal] = '.';
				}
			}
		}
	}
	// 땅이 모두 포함될 수 있도록 땅이 있는 곳을 찾기..
	int sh = 100, sy = 100, fh = -1, fy = -1;

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 'X') {
				if (sh > hang) sh = hang;
				if (fh < hang) fh = hang;
				if (sy > yal) sy = yal;
				if (fy < yal) fy = yal;
			}
		}
	}
	//출력
	for (int hang = sh; hang <= fh; hang++) {
		for (int yal = sy; yal <= fy; yal++) {
			printf("%c", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}