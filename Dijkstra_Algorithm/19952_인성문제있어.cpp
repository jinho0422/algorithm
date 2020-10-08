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
	int h, y, f; // h : hang, y ; yal, f : ���� ������ �ִ� ��!
}pos;

queue<pos> Q;

void BFS(int hang, int yal, int power);

int main() {
	//�Է�
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//�ʱ�ȭ
		memset(board, 0, sizeof(board));
		memset(dij_board, -1, sizeof(dij_board));
		scanf("%d %d %d %d %d %d %d %d", &N, &M, &O, &F, &sh, &sy, &fh, &fy);
		for (int a, b, c, i = 0; i < O; i++) {
			scanf("%d %d %d", &a, &b, &c);
			board[a][b] = c;
		}
		//���������� BFS
		BFS(sh, sy, F);
		//���
		if (dij_board[fh][fy] == -1) printf("�μ� �����־�??\n");
		else printf("���߾�!!\n");
	}
	return 0;
}

void BFS(int hang, int yal, int power) {
	dij_board[hang][yal] = power; // �������� ���� ���� ����..
	Q.push(pos({ hang, yal, power }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		if (p.f < 1) continue; // ���� 0�����̸� ���̻� ������ �� �����Ƿ� continue..

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY <= 0 || newY > N || newX <= 0 || newX > M) continue;
			// ������ ��ġ���� �����̴� ���� ũ�Ⱑ ���ų� ���� ��, �����̴� ���� ������ ���ŉ���ź��� ũ��..�̵�
			if (board[p.h][p.y] >= board[newY][newX]) {
				if (dij_board[newY][newX] < p.f - 1) {
					dij_board[newY][newX] = p.f - 1;
					Q.push(pos({ newY, newX, dij_board[newY][newX] }));
				}
			}
			// �̵��� ���� ���纸�� ���� �� ������ �ִ� ���� �̵��� �� - ������ ���̺��� Ŭ �� ���� ������ ���ŵƴ��ͺ��� ũ�� �̵�..
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