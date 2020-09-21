#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>
using namespace std;

int N;
char str[51];
int board[51][51];
int dij_board[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : �������� ������ Ƚ��..
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;

int BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
			dij_board[hang][yal] = INF;
		}
	}
	printf("%d\n", BFS(0, 0));
	return 0;
}

int BFS(int hang, int yal) {
	dij_board[hang][yal] = 0;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		// ������ ��ġ�� �����ϸ� ���..
		Q.pop();
		if (p.h == N - 1 && p.y == N - 1) {
			return p.cnt;
		}

		for (int dir = 0; dir < 4; dir++ ) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
			// ������̸�
			if (board[newY][newX] == 1) {
				// ������ �Դ� ����� ���纸�� �������� �� ���� �������� �Դٸ� ����..
				if (dij_board[newY][newX] > dij_board[p.h][p.y]) {
					dij_board[newY][newX] = dij_board[p.h][p.y];
					Q.push(pos({ newY, newX, dij_board[newY][newX] }));
				}
			}
			//�������̸�
			else if (board[newY][newX] == 0) {
				// ������ �Դ� ����� ����� ����� + 1�� �ص� �� ���� �������� �Դٸ� ����..��
				if (dij_board[newY][newX] > dij_board[p.h][p.y] + 1) {
					dij_board[newY][newX] = dij_board[p.h][p.y] + 1;
					Q.push(pos({ newY, newX, dij_board[newY][newX] }));
				}
			}
		}
	}
	//�������� ���ϸ� 0 return..
	return 0;
}