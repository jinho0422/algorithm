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
	// ���� �� �ٴٿ� ������ ���� ����� ã��..
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
	// ���� ��� ���Ե� �� �ֵ��� ���� �ִ� ���� ã��..
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
	//���
	for (int hang = sh; hang <= fh; hang++) {
		for (int yal = sy; yal <= fy; yal++) {
			printf("%c", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}