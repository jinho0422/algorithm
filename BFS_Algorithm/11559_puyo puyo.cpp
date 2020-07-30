#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

char str[8];
char board[14][8];
bool check[14][8];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;

typedef struct _pos {
	int h, y;
}pos;

pos checkPoint[73];
int num;

queue<pos> Q;
queue<char> colorBoll;

void BFS(int hang, int yal);

int main() {
	for (int hang = 0; hang < 12; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < 6; yal++) {
			board[hang][yal] = str[yal];
		}
	}

	while (1) {
		bool flag = false;
		for (int hang = 0; hang < 12; hang++) {
			for (int yal = 0; yal < 6; yal++) {
				if (board[hang][yal] != '.' && !check[hang][yal]) {
					num = 0;
					BFS(hang, yal);
					if (num > 3) {
						flag = true;
						for (int s = 0; s < num; s++) {
							board[checkPoint[s].h][checkPoint[s].y] = '.';
						}

						for (int yal = 0; yal < 6; yal++) {
							for (int hang = 11; hang >= 0; hang--) {
								if (board[hang][yal] != '.') {
									colorBoll.push(board[hang][yal]);
									board[hang][yal] = '.';
								}
							}
							int sz = colorBoll.size();

							for (int i = 0; i < sz; i++) {
								char p = colorBoll.front();
								colorBoll.pop();
								board[11 - i][yal] = p;
							}
						}
					}
				}
			}
		}

		if (flag) {
			result++;
			memset(check, false, sizeof(check));
		}
		else if (!flag) break;
	}
	printf("%d\n", result);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	checkPoint[num++] = { hang, yal };

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > 11 || newX < 0 || newX > 5) continue;

			if (board[newY][newX] == board[hang][yal] && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
				checkPoint[num++] = { newY, newX };
			}
		}
	}
}