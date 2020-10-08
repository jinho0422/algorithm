#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int board[4][5][5][5];
int tmpBoard[5][5][5]; // board�� ������ �̷θ� ���� board
bool check[5][5][5];
int dirY[6] = { -1, 1, 0 ,0, 0, 0 };
int dirX[6] = { 0, 0, -1, 1, 0 ,0 };
int dirZ[6] = { 0, 0, 0, 0, -1, 1 };
int tmp[5]; // ��� ȸ���� ������ �ִ� �迭
int orders[5]; // � ���� ��� ��ġ�� ���� ������ �ִ� �迭
bool ordersCheck[5];
int time, result; // time : �̷θ� Ż���ϴ� ����� �̵���, result : ���� �����
bool flag, onFlag; // flag : �̷θ� Ż���� �� �ִ��� �Ǵ�, onFlag : ��� ���� 1�ϰ�� ������� 12�̹Ƿ� Ż��..

typedef struct _pos {
	int h, y, z;
}pos;

void DFS(int depth);

int main() {
	//�Է�
	result = 987654321;
	for (int i = 0; i < 5; i++) {
		for (int hang = 0; hang < 5; hang++) {
			for (int yal = 0; yal < 5; yal++) {
				scanf("%d", &board[0][i][hang][yal]);
				if (board[0][i][hang][yal] == 0) onFlag = true;
			}
		}
	}
	// ����ȸ���� �ֱ�(0��, 90��, 180��, 270��)
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			for (int hang = 0; hang < 5; hang++) {
				for (int yal = 0; yal < 5; yal++) {
					board[i][j][hang][yal] = board[i - 1][j][yal][4 - hang];
				}
			}
		}
	}
	// ��纸�尪�� 1�� �� ����� 12..
	if (!onFlag) {
		printf("12\n");
		return 0;
	}

	DFS(0);
	//���
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}
//�̷�Ż��
void BFS() {
	check[0][0][0] = true;
	queue<pos> Q;
	time = 0;
	Q.push(pos({ 0, 0, 0 }));

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			if (p.h == 4 && p.y == 4 && p.z == 4) {
				flag = true;
				return;
			}
			for (int dir = 0; dir < 6; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				int newZ = p.z + dirZ[dir];

				if (newY < 0 || newY > 4 || newX < 0 || newX > 4 || newZ < 0 || newZ > 4) continue;

				if (tmpBoard[newZ][newY][newX] == 1 && !check[newZ][newY][newX]) {
					check[newZ][newY][newX] = true;
					Q.push(pos({ newY, newX, newZ }));
				}
			}
		}
		time++;
		if (time > result) return;
	}
}
// ȸ���� 5�� ������ ���带 ��� ��ġ�� �����ų�� orders �迭�� �ִ´�..
void DFS1(int depth) {
	if (depth == 5) {
		//�ʱ�ȭ
		memset(check, false, sizeof(check));
		flag = false;
		//tmpBoard�� �̷θ� �����..
		for (int i = 0; i < 5; i++) {
			for (int hang = 0; hang < 5; hang++) {
				for (int yal = 0; yal < 5; yal++) {
					tmpBoard[i][hang][yal] = board[tmp[i]][orders[i]][hang][yal];
				}
			}
		}
		//��������� ������ ������ �̵��� �� �ִ� ����� BFS�� ���� �̷��̵�
		if (tmpBoard[0][0][0] == 1 && tmpBoard[4][4][4] == 1) BFS();
		// �̷θ� Ż���ߴٸ� ����� ����..
		if (flag) {
			if (result > time) result = time;
			return;
		}
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (!ordersCheck[i]) {
			ordersCheck[i] = true;
			orders[depth] = i;
			DFS1(depth + 1);
			orders[depth] = 0;
			ordersCheck[i] = false;
		}
	}
}
// 5�� ������ ���带 �󸶳� ȸ���� ������ tmp�� �ִ´�
void DFS(int depth) {
	if (depth == 5) {
		DFS1(0);
		return;
	}
	for (int i = 0; i < 4; i++) {
		tmp[depth] = i;
		DFS(depth + 1);
		tmp[depth] = 0;
	}
}