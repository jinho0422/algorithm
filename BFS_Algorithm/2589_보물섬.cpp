#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;
int max_result;

typedef struct _pos {
	int h, y;
}pos;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 'L') {
				memset(check, false, sizeof(check));
				BFS(hang, yal);
				if (max_result < result) max_result = result;
			}
		}
	}
	printf("%d\n", max_result);
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal}));
	result = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		bool flag = false;
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] == 'L' && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					flag = true;
				}
			}
		}
		if(flag) result++;
	}
}
