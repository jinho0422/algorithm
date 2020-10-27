#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[126][126];
int dijBoard[126][126];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : 각 지점에서의 최소값을 가지고있는다.
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

void dijkstra(int hang, int yal);


int main() {
	int t = 1;
	while (1) {
		scanf("%d", &N);
		if (N == 0) break;
		//초기화
		memset(board, 0, sizeof(board));
		memset(dijBoard, 0, sizeof(dijBoard));

		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
				dijBoard[hang][yal] = INF;
			}
		}
		dijkstra(0, 0);
		printf("Problem %d: %d\n", t++, dijBoard[N - 1][N - 1]);

	}

	return 0;
}
// 각 지점의 최소값 갱신..
void dijkstra(int hang, int yal) {
	int result = INF;
	dijBoard[hang][yal] = board[hang][yal];
	Q.push(pos({ hang, yal, board[hang][yal] }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		if (p.cnt >= result) continue;
		if (p.h == N - 1 && p.y == N - 1) {
			if (result > board[N - 1][N - 1]) result = board[N - 1][N - 1];
			continue;
		}

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (dijBoard[newY][newX] > board[newY][newX] + p.cnt) {
				dijBoard[newY][newX] = board[newY][newX] + p.cnt;
				Q.push(pos({ newY, newX, dijBoard[newY][newX] }));
			}
		}
	}
}