#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, M, T;
int board[101][101];
bool check[2][101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;
typedef struct _pos {
	int h, y, cnt, flag; // ��, ��, �� �Ÿ�, ���� ȹ���ߴ��� ���ߴ���..
}pos;

queue<pos> Q;

void solve(int hang, int yal, int go);

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &T);
	result = INF;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	//BFS Ž���� ����..
	solve(0, 0, 0);
	if (result > T) printf("Fail\n");
	else printf("%d\n", result);
	return 0;
}
void solve(int hang, int yal, int go) {
	check[0][0][0] = true;
	Q.push(pos({ hang, yal, go, 0 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		// ���ִԿ��� ����������, ����� ����..
		if (p.h == N - 1 && p.y == M - 1) {
			if (result > p.cnt) result = p.cnt;
			continue;
		}
		//��������� �̵��Ÿ��� ���ٸ� continue..
		if (p.cnt > result) continue;
		//���� ���� ȹ������ ���ߴٸ�..
		if (p.flag == 0) {
			//�����¿츦 ����
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// �� �� �ִ� ���̸� ����
				if (board[newY][newX] == 0 && !check[0][newY][newX]) {
					check[0][newY][newX] = true;
					Q.push(pos({ newY, newX,p.cnt + 1, 0 }));
				}
				//���� ȹ���� �� ������ p.flag�� 1�� �����..
				if (board[newY][newX] == 2 && !check[0][newY][newX]) {
					check[0][newY][newX] = true;
					check[1][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt + 1, 1 }));
				}
			}
		}
		//���� ������ ������ ���� ������ �ִ� check[1][hang][yal]���� visited�� üũ�ϸ� �����δ�.
		else {
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (!check[1][newY][newX]) {
					check[1][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt + 1, 1 }));
				}
			}
		}
	}
}