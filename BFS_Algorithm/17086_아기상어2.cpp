/*
	N*Mũ���� ������ �Ʊ� �� �������� �ִ�. �����ǿ� �Ʊ�� �ִ� ���� 1, ���� ���� 0�̴�.
	�Ʊ�� ���� �����ǿ��� �Ʊ���� ��,��, ��, ��, �밢������ �Ʊ�� �������ִ� �����Ÿ��� �ִ밪�� ���ϴ� �˰���

	�����ǿ��� �Ʊ�� ���°����� BFS�� �̿��Ͽ� �Ÿ��� üũ�ϸ鼭 �ִ��� �Ÿ��� �����ϴ� �˰��� ����..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int board[50][50];
bool check[50][50];
int dirY[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };//��,��,��,��,�밢��
int dirX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int result;

typedef struct _pos {
	int h, y;
}pos;

int BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0) {//�����ǿ��� �� ���� ��..
				int length = BFS(hang, yal);// BFS�� ���� �����Ÿ��� ����..
				if (result < length) result = length;//�����Ÿ� �ִ밪 ����..
				memset(check, false, sizeof(check));// BFS�� ����� �� visited�� �ϱ� ���� check�迭 ����..
			}
		}
	}
	printf("%d\n", result);

	return 0;
}

int BFS(int hang, int yal) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int time = 0;

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			if (board[p.h][p.y] == 1) return time;//�� ������ return �Ÿ�..

			for (int dir = 0; dir < 8; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;//�������� ����� continue..

				if (board[newY][newX] == 0 && !check[newY][newX]) {// �����ѿ����� ������ ��..
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
				if (board[newY][newX] == 1 && !check[newY][newX]) {//�� ������ ��..
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
			}
		}
		time++;// Qũ�⸦ ��� ���� �Ÿ�����..
	}
}