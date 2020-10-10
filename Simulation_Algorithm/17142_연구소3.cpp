#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[51][51];
bool check[51][51];
int tmpBoard[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int zero, tmpZero;
int time, result;


typedef struct _pos {
	int h, y; //h : hang, y : yal, f : Ȱ�����̷������� üũ..
	bool f;
}pos;
queue<pos> Q;
vector<pos> Vec;

void DFS(int depth, int start);

int main() {
	//�Է�
	result = 987654321;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal, false }));// ���̷����̸� vector�� �ִ´�.		
			else if (board[hang][yal] == 0) zero++; // 0�ΰ��̸���� üũ..
		}
	}
	//���� 0�ΰ��� ������ 0 ���..
	if (zero == 0) {
		printf("0\n");
		return 0;
	}
	DFS(0, 0);
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}
// ���̷��� Ȯ���Ų��.
void BFS() {
	// Ȱ�����̷����� Q�� �ִ´�.
	for (int s = 0; s < Vec.size(); s++) {
		if (Vec[s].f) {
			Q.push(pos({ Vec[s].h, Vec[s].y }));
			check[Vec[s].h][Vec[s].y] = true;
		}
	}
	time = 0;
	while (!Q.empty()) {
		if (time >= result) return; // ��������� ũ�� ����..
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// 0�� ����
				if (tmpBoard[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					tmpZero--;
				}
				// ��Ȱ�� ����..
				if (tmpBoard[newY][newX] == 2 && !check[newY][newX]) {
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
			}
		}
		time++;	
		if (tmpZero == 0) return;
	}
}
// ��Ȱ�� ���̷����߿� M���� Ȱ�����̷����� �����..
void DFS(int depth, int start) {
	if (depth == M) {
		//�ʱ�ȭ
		while (!Q.empty()) Q.pop();
		memset( check, false, sizeof(check));
		memcpy(tmpBoard, board, sizeof(tmpBoard));
		tmpZero = zero;
		BFS();
		// ������ ä���ٸ�..
		if (tmpZero == 0) {
			if (result > time) result = time;
		}
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		if (!Vec[s].f) {
			Vec[s].f = true;
			DFS(depth + 1, s + 1);
			Vec[s].f = false;
		}
	}
}