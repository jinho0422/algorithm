#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>

using namespace std;

int N, L, R;
int board[51][51];
int tmpboard[51][51]; // ��� ������ �Ǵ� �� �α� �̵��� ������ ���� �α����
bool check[51][51]; // ���� �湮 üũ..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int resultTime;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // �α��̵��� ������ ������ ���� vector
queue<pos> Q; 

int BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d %d", &N, &L, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	while (1) {
		bool moveCheck = false; // �α��̵��� �Ͼ���� �Ǵ��ϴ� check..
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if (!check[hang][yal]) { // ��� ������ ���� �� ���� ���� ���� ������ �ִٸ�..
					int sum = BFS(hang, yal); // �α��̵��� �������� �Ǵ� �� �� �ִ� �Լ�..
					int sz = Vec.size();
					if (sz>= 2) moveCheck = true; // ���� Vectorũ�Ⱑ 2�̻��̸� ���� �� �α��� ������ �� �ִ� �Ǵ�..
					for (int i = 0; i < sz; i++) { // ������ �� �ִ� ���� �α� ��ü�� ��ճ��� �־��ش�..
						tmpboard[Vec[i].h][Vec[i].y] = sum / sz;
					}
					Vec.clear(); // ���� ������ �� �ִ� ������ �Ǵ��ϱ� ���� �ʱ�ȭ..
				}
			}
		}
		if (!moveCheck) break; // ������ �� ������ break..
		else {
			resultTime++; // ����� ����(������ �� ������)
			memcpy(board, tmpboard, sizeof(tmpboard)); // tmpboard�� ������ ���� �α� ����� board�� ����..
			memset(check, false, sizeof(check)); // ���� �湮 üũ �Լ� �ʱ�ȭ
		}
	}
	//���
	printf("%d\n", resultTime);
	return 0;
}

int BFS(int hang, int yal) {
	int populationSum = 0; // �̵��� �� �ִ� ��� ������ �α��� ��
	check[hang][yal] = true; // ���� �湮 üũ..
	Q.push(pos({ hang, yal }));
	Vec.push_back(pos({ hang, yal }));
	populationSum += board[hang][yal];
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N- 1) continue;
			// ������ ������ �� �ִ��� �Ǵ��ؼ� Vector�� �ִ´�..
			if ((abs(board[p.h][p.y] - board[newY][newX]) >= L) && (abs(board[p.h][p.y] - board[newY][newX]) <= R) && !check[newY][newX]) {
				check[newY][newX] = true;
				Vec.push_back(pos({ newY, newX }));
				Q.push(pos({ newY, newX }));
				populationSum += board[newY][newX];
			}
		}
	}
	return populationSum;
}