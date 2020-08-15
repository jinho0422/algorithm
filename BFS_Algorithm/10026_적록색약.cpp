#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N;
char str[102];
char board[102][102];
bool check[102][102];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

queue<pos> Q;

void NOBFS(int hang, int yal);
void BFS(int hang, int yal);

int main() {
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	int result = 0;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (!check[hang][yal]) {
				NOBFS(hang, yal);
				result++;
			}
		}
	}
	printf("%d ", result);

	result = 0;
	memset(check, false, sizeof(check));

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (!check[hang][yal]) {
				BFS(hang, yal);
				result++;
			}
		}
	}
	printf("%d\n", result);
	return 0;
}

void NOBFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (board[hang][yal] == board[newY][newX] && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	bool flag = false;

	if (board[hang][yal] == 'R' || board[hang][yal] == 'G') flag = true;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (flag) {
				if (!check[newY][newX]) {
					if (board[newY][newX] == 'R' || board[newY][newX] == 'G') {
						check[newY][newX] = true;
						Q.push(pos({ newY, newX }));
					}
				}
			}
			else {
				if (board[newY][newX] == 'B' && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
			}
		}
	}
}