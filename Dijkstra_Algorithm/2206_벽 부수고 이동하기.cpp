#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>
using namespace std;

int N, M;
char str[1001];
int board[1001][1001];
int dij_board[2][1001][1001];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt, r; // h : hang, y : yal, cnt : 벽을 부쉬지 않았으면 0, 부셧으면 1, r : 움직인 횟수
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.r > q.r;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

int BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal] - '0';
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				dij_board[i][hang][yal] = INF;
			}
		}
	}

	printf("%d\n",BFS(0, 0));

	return 0;
}

int BFS(int hang, int yal) {
	dij_board[0][hang][yal] = 1;
	Q.push(pos({ hang, yal, 0, 1 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		//목적지 도착..
		if (p.h == N - 1 && p.y == M - 1) {
			return p.r;
		}

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
			// 벽일 때
			if (board[newY][newX] == 1) {
				if (p.cnt == 1) continue; // 벽을 한번 부셨으면 continue..
				// 이전의 움직임보다 더 작다면 갱신..
				if (dij_board[p.cnt + 1][newY][newX] > dij_board[p.cnt][p.h][p.y] + 1) {
					dij_board[p.cnt + 1][newY][newX] = dij_board[p.cnt][p.h][p.y] + 1;
					Q.push(pos({ newY, newX, p.cnt + 1, dij_board[p.cnt + 1][newY][newX] }));
				}
			}
			//벽이 아닐 때
			else if (board[newY][newX] == 0) {
				//이전의 움직임보다 더 작다면 갱신..
				if (dij_board[p.cnt][newY][newX] > dij_board[p.cnt][p.h][p.y] + 1) {
					dij_board[p.cnt][newY][newX] = dij_board[p.cnt][p.h][p.y] + 1;
					Q.push(pos({ newY, newX, p.cnt, dij_board[p.cnt][newY][newX] }));
				}
			}
		}
	}
	//도착할 수 없는 경우
	return -1;
}