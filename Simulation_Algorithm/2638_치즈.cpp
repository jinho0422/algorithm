#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int board[101][101];
int checkNum[101][101];
bool check[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int chezz;
int result;

typedef struct _pos {
	int h, y;
}pos;

void BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) chezz++; // ġ���� ũ�� ����..
		}
	}
	while (1) {
		BFS(0, 0); // �ܺΰ��⸦ üũ..
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (board[hang][yal] == 1) { // ġ���̸�
					int cnt = 0;
					for (int dir = 0; dir < 4; dir++) { // �����¿츦����
						int newY = hang + dirY[dir];
						int newX = yal + dirX[dir];

						if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

						if (check[newY][newX] == 1) { // �ܺΰ���� ������
							cnt++; // cnt ����
							if (cnt == 2) { // �ܺΰ��⸦ 2���̻� ������
								board[hang][yal] = 0; // ġ� ���δ�..
								chezz--;
								break;
							}
						}
					}
				}
			}
		}
		result++; // ����� ����..
		if(chezz == 0) break; // ġ� ��� ������ break;
		memset(check, false, sizeof(check)); // �ܺΰ��� �ʱ�ȭ..
	}
	printf("%d\n", result);
	return 0;
}
// �ܺΰ���üũ..
void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}