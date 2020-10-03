#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[1 << 5][51][51];
char num;
int num1;

typedef struct _pos {
	int h, y, cnt, time;
}pos;
pos start[1];
pos endd[1];

void solve(int hang, int yal);

int main() {
	scanf("%d %d", &M, &N);
	num = 'a';
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];

			if (board[hang][yal] == 'S') {
				board[hang][yal] = '.';
				start[0] = { hang, yal };
			}
			if (board[hang][yal] == 'E') {
				board[hang][yal] = '.';
				endd[0] = { hang, yal };
			}

			if (board[hang][yal] == 'X') {
				board[hang][yal] = num;
				num++;
				num1++;
			}
		}
	}

	solve(start[0].h, start[0].y);

	return 0;
}

void solve(int hang, int yal) {
	int dirY[4] = { -1, 0, 0, 1 };
	int dirX[4] = { 0, -1, 1, 0 };
	bool flag = false;
	queue<pos> Q;
	check[0][hang][yal] = true;
	Q.push(pos({ hang, yal, 0, 0 }));

	while (!Q.empty()) {
		int sz = Q.size();

		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			bool flag = false;
			for (int i = 0; i < num1; i++) {
				if ((p.cnt & 1 << i) == 0) {
					flag = true;
					if (flag) break;
				}
			}

			if (!flag) {
				if (p.h == endd[0].h && p.y == endd[0].y) {
					printf("%d\n", p.time);
					return;
				}
			}

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

				if (board[newY][newX] == '.' && !check[p.cnt][newY][newX]) {
					check[p.cnt][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt, p.time + 1 }));
				}

				if (board[newY][newX] >= 'a' && board[newY][newX] <= 'z') {
					int new_cnt = p.cnt | (1 << board[newY][newX] - 'a');
					if (!check[new_cnt][newY][newX]) {
						check[new_cnt][newY][newX] = true;
						Q.push(pos({ newY, newX, new_cnt, p.time + 1 }));
					}
				}

			}
		}
	}
}