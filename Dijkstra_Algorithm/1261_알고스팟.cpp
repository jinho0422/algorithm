#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
char str[101];
int board[100][100];
int dij_board[100][100];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

int result;

typedef struct _pos {
	int h, y, wall_cnt; // h : hang, y : yal, wall_cnt : 벽을 부순 횟수
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.wall_cnt > q.wall_cnt;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

int main() {
	//입력
	scanf("%d %d", &M, &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal] - '0';
			dij_board[hang][yal] = INF;
		}
	}

	dij_board[0][0] = board[0][0];
	Q.push(pos({ 0, 0, board[0][0] })); // 초기값 저장.

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (p.wall_cnt > dij_board[p.h][p.y]) continue; // 이전의 벽 부순횟수가 더 작으면 continue..

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (dij_board[newY][newX] > dij_board[p.h][p.y] + board[newY][newX]) {
				dij_board[newY][newX] = dij_board[p.h][p.y] + board[newY][newX];
				Q.push(pos({ newY, newX, dij_board[newY][newX] }));
			}
		}
	}
	printf("%d\n", dij_board[N - 1][M - 1]);
	return 0;
}