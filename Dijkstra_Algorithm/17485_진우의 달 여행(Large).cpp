#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int board[1001][1001];
int dij_board[4][1001][1001]; // 1 : leftdown, 2 : down, 3 : rightdown
int dirY[4] = { 0, 1, 1, 1 };
int dirX[4] = { 0, -1, 0, 1 };
int result;

typedef struct _pos {
	int h, y, d;
}pos;

queue<pos> Q;

void BFS();

int main() {
	//�Է� ���� hang == 0�̸� ������̹Ƿ� Q�� �־��ش�.
	result = 2147000000;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (hang == 0) Q.push(pos({ hang, yal, 0 }));

		}
	}
	//dijkstra�� ����ϱ� ���� dij_board�ʱ�ȭ.. dij_board�� 3������ ������ ���⿡ ���� �� �� �ֱ� ����..
	for (int i = 0; i < 4; i++) {
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (i == 0 && hang == 0) dij_board[i][hang][yal] = board[hang][yal];
				else dij_board[i][hang][yal] = 2147000000;
			}
		}
	}

	BFS();

	//����� ����
	for (int i = 0; i < 4; i++) {
		for (int yal = 0; yal < M; yal++) {
			if (result > dij_board[i][N - 1][yal]) result = dij_board[i][N - 1][yal];
		}
	}
	printf("%d\n", result);
	return 0;
}

void BFS() {
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			for (int dir = 1; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (p.d == dir) continue; // ���� �������� �ι��̻� �� �� �����Ƿ�
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue; // ��谪 ����� �ʱ� ����..
				//���� ���⿡ ���� �� ������ ���� ������ġ�� ���� ���� ������ ����..
				if (dij_board[dir][newY][newX] > dij_board[p.d][p.h][p.y] + board[newY][newX]) {
					dij_board[dir][newY][newX] = dij_board[p.d][p.h][p.y] + board[newY][newX];
					Q.push(pos({ newY, newX, dir }));
				}
			}
		}
	}
}