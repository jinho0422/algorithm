#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int xx, yy, xxx, yyy;
char str[303];
int board[303][303];
bool check[303][303];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec;
queue<pos> Q;

void BFS();

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	scanf("%d %d %d %d", &xx, &yy, &xxx, &yyy);
	for (int hang = 1; hang <= N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal + 1] = str[yal] - '0';
		}
	}
	board[xx][yy] = 0, board[xxx][yyy] = 1; // �ֳ��̰� �ִ� ���� 0, ������ �ִ� ���� 1

	while (1) {
		bool flag = false; // ������ ã�Ҵ��� �Ǵ��ϴ� flag
		result++; // �����
		BFS();
		for (int s = 0; s < Vec.size(); s++) { // ������ ���� ����� �ִ°��� �Ѿ�Ʈ����(1 --> 0)
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[s].h + dirY[dir];
				int newX = Vec[s].y + dirX[dir];
				if (newY == xxx && newX == yyy) flag = true; // ������ ã���� flag = true;

				if (newY <= 0 || newY > N || newX <= 0 || newX > M) continue;

				if (board[newY][newX] == 1) {
					board[newY][newX] = 0;
				}
			}
		}
		if (flag) break;
		// �ʱ�ȭ
		Vec.clear();
		memset(check, false, sizeof(check));
	}
	//���
	printf("%d\n", result);
	return 0;
}

void BFS() {
	check[xx][yy] = true;
	Q.push(pos({ xx, yy }));
	Vec.push_back(pos({ xx, yy }));
		while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY <= 0 || newY > N || newX <= 0 || newX > M ) continue;
			// 0�ΰ��� Vec�� ����
			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				Vec.push_back(pos({ newY, newX }));
				Q.push(pos({ newY, newX }));
			}
		}
	}
}