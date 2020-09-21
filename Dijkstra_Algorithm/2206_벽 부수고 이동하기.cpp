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
	int h, y, cnt, r; // h : hang, y : yal, cnt : ���� �ν��� �ʾ����� 0, �μ����� 1, r : ������ Ƚ��
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.r > q.r;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

int BFS(int hang, int yal);

int main() {
	//�Է�
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
		//������ ����..
		if (p.h == N - 1 && p.y == M - 1) {
			return p.r;
		}

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
			// ���� ��
			if (board[newY][newX] == 1) {
				if (p.cnt == 1) continue; // ���� �ѹ� �μ����� continue..
				// ������ �����Ӻ��� �� �۴ٸ� ����..
				if (dij_board[p.cnt + 1][newY][newX] > dij_board[p.cnt][p.h][p.y] + 1) {
					dij_board[p.cnt + 1][newY][newX] = dij_board[p.cnt][p.h][p.y] + 1;
					Q.push(pos({ newY, newX, p.cnt + 1, dij_board[p.cnt + 1][newY][newX] }));
				}
			}
			//���� �ƴ� ��
			else if (board[newY][newX] == 0) {
				//������ �����Ӻ��� �� �۴ٸ� ����..
				if (dij_board[p.cnt][newY][newX] > dij_board[p.cnt][p.h][p.y] + 1) {
					dij_board[p.cnt][newY][newX] = dij_board[p.cnt][p.h][p.y] + 1;
					Q.push(pos({ newY, newX, p.cnt, dij_board[p.cnt][newY][newX] }));
				}
			}
		}
	}
	//������ �� ���� ���
	return -1;
}