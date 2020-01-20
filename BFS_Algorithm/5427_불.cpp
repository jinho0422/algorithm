#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int N, M;
char str[1001];
char board[1001][1001];
bool check[1001][1001];
bool check_fire[1001][1001];
bool flag;
int time;

typedef struct _pos {
	int h, y;
}pos;
pos start[1];
queue<pos> Q;

void solve(int hang, int yal);

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		flag = false;
		time = 0;
		scanf("%d %d", &M, &N);

		for (int hang = 0; hang < N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang][yal] = str[yal];

				if (board[hang][yal] == '@') start[0] = { hang, yal };
				if (board[hang][yal] == '*') {
					check_fire[hang][yal] = true;
					Q.push(pos({ hang, yal }));
				}
			}
		}

		solve(start[0].h, start[0].y);

		if (!flag) printf("IMPOSSIBLE\n");

		while (!Q.empty()) Q.pop();
		memset(check, false, sizeof(check));
		memset(check_fire, false, sizeof(check_fire));
	}

	return 0;
}


void solve(int hang, int yal) {
	int dirY[4] = { -1, 0, 0, 1 };
	int dirX[4] = { 0, -1, 1, 0 };

	queue<pos> Q_people;
	check[hang][yal] = true;
	Q_people.push(pos({ hang, yal }));

	while (1) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

				if (board[newY][newX] == '.' || board[newY][newX] == '@') {
					if (!check_fire[newY][newX]) {
						check_fire[newY][newX] = true;
						Q.push(pos({ newY, newX }));
					}
				}
			}
		}

		int sz1 = Q_people.size();
		for (int s = 0; s < sz1; s++) {
			pos p1 = Q_people.front();
			if (board[p1.h][p1.y] == '@') board[p1.h][p1.y] = '.';
			Q_people.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p1.h + dirY[dir];
				int newX = p1.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) {
					flag = true;
					time++;
					printf("%d\n", time);
					return;
				}

				if (board[newY][newX] == '.' && !check[newY][newX] && !check_fire[newY][newX]) {
					check[newY][newX] = true;
					board[newY][newX] = '@';
					Q_people.push(pos({ newY, newX }));
				}
			}
		}
		time++;
		if (sz == 0 && sz1 == 0 ) break;
		
	}
}