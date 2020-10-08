#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int N, M, O, F, sh, sy, fh, fy;
int board[101][101];
int dij_board[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, f; // h : hang, y ; yal, f : 현재 가지고 있는 힘!
}pos;

queue<pos> Q;

void BFS(int hang, int yal, int power);

int main() {
	//입력
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//초기화
		memset(board, 0, sizeof(board));
		memset(dij_board, -1, sizeof(dij_board));
		scanf("%d %d %d %d %d %d %d %d", &N, &M, &O, &F, &sh, &sy, &fh, &fy);
		for (int a, b, c, i = 0; i < O; i++) {
			scanf("%d %d %d", &a, &b, &c);
			board[a][b] = c;
		}
		//시작점에서 BFS
		BFS(sh, sy, F);
		//출력
		if (dij_board[fh][fy] == -1) printf("인성 문제있어??\n");
		else printf("잘했어!!\n");
	}
	return 0;
}

void BFS(int hang, int yal, int power) {
	dij_board[hang][yal] = power; // 시작점에 시작 힘을 저장..
	Q.push(pos({ hang, yal, power }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		if (p.f < 1) continue; // 힘이 0이하이면 더이상 움직일 수 없으므로 continue..

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY <= 0 || newY > N || newX <= 0 || newX > M) continue;
			// 현재의 위치에서 움직이는 곳의 크기가 같거나 낮을 때, 움직이는 힘이 그전에 갱신됬던거보다 크면..이동
			if (board[p.h][p.y] >= board[newY][newX]) {
				if (dij_board[newY][newX] < p.f - 1) {
					dij_board[newY][newX] = p.f - 1;
					Q.push(pos({ newY, newX, dij_board[newY][newX] }));
				}
			}
			// 이동할 곳이 현재보다 높을 때 가지고 있는 힘이 이동할 곳 - 현재의 높이보다 클 때 힘이 그전에 갱신됐던것보다 크면 이동..
			else {
				if (p.f >= board[newY][newX] - board[p.h][p.y]) {
					if (dij_board[newY][newX] < p.f - 1) {
						dij_board[newY][newX] = p.f - 1;
						Q.push(pos({ newY, newX, dij_board[newY][newX] }));
					}
				}
			}
		}
	}
}