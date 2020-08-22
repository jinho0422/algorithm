#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int board[101][101];
bool check[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int cheeze;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // ������ ��ǥ�� �ֱ�����..
queue<pos> Q; // ������ ������ ���ϱ� ���� ..

void air(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) cheeze++; // ġ���� ũ��
		}
	}
	int timeResult = 0; // �ð������
	int meltcnt = 0; // �ð��� ���� ġ���� ũ��
	while (1) {
		// ġ� �� ������ ���..
		if (cheeze == 0) {
			printf("%d\n%d\n", timeResult, meltcnt);
			break;
		}
		timeResult++;
		meltcnt = 0;
		air(0, 0);// ������ ������ ���ϱ�����..
		//������ ������ ���ƺ��� �ֺ��� ġ� ������ ���δ�.,
		for (int s = 0; s < Vec.size(); s++) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[s].h + dirY[dir];
				int newX = Vec[s].y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] == 1) {
					meltcnt++;
					board[newY][newX] = 0;
				}
			}
		}
		// ������ ġ��� ���� ġ� ����..
		cheeze -= meltcnt;
		//�ʱ�ȭ
		Vec.clear();
		memset(check, false, sizeof(check));
	}
	return 0;
}

void air(int hang, int yal) {
	check[hang][yal] = true;
	Vec.push_back(pos({ hang, yal }));
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
				Vec.push_back(pos({ newY, newX }));
			}
		}
	}
}