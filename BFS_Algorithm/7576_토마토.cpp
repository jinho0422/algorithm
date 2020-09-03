#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int board[1001][1001];
bool check[1001][1001];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int zero;
int result_time;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec;
queue<pos> Q;

void BFS();

int main() {
	scanf("%d %d", &M, &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 0) zero++;
			else if (board[hang][yal] == 1) Vec.push_back(pos({ hang, yal }));
		}
	}
	BFS();
	if (zero == 0) printf("%d\n", result_time);
	else printf("-1\n");

	return 0;
}

void BFS() {
	for (int i = 0; i < Vec.size(); i++) {
		check[Vec[i].h][Vec[i].y] = true;
		Q.push(pos({ Vec[i].h, Vec[i].y }));
	}

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

				if (board[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					zero--;
					flag = true;
				}
			}
		}
		if(flag) result_time++;
	}
}