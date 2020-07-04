#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int dirY[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int shark[4][8];
int board[6][6];
bool check[6][6];
int result;

typedef struct _pos {
	int n, d;
	bool flag;
}pos;
vector<pos> Vec;

pos sharkPoint[1];

bool cmp(const pos& p, const pos& q) {
	return p.n < q.n;
}

void DFS(int sum, int sharkD, int hang, int yal);

void changeArea(int i, int hang, int yal, int j, int k);

int main() {
	for (int hang = 0; hang < 4; hang++) {
		for (int yal = 0; yal < 8; yal++) {
			scanf("%d", &shark[hang][yal]);
		}
	}

	for (int hang = 0; hang < 4; hang++) {
		for (int yal = 0; yal < 8;) {
			Vec.push_back(pos({ shark[hang][yal], shark[hang][yal + 1], false }));
			yal += 2;
		}
	}
	int numbers = 0;


	for (int hang = 0; hang < 4; hang++) {
		for (int yal = 0; yal < 4; yal++) {
			board[hang][yal] = Vec[numbers++].n;
		}
	}
	sort(Vec.begin(), Vec.end(), cmp);


	sharkPoint[0].n = board[0][0], sharkPoint[0].d = Vec[board[0][0] - 1].d;
	Vec[board[0][0] - 1].flag = true;
	DFS(sharkPoint[0].n, sharkPoint[0].d, 0, 0);
	printf("%d\n", result);

	return 0;
}


void changeArea(int i, int hang, int yal, int j, int k) {

	bool checkflag = false;
	int cnt = 0;
	while (1) {
		int newY = hang + dirY[Vec[i].d];
		int newX = yal + dirX[Vec[i].d];

		if ((newY == j && newX == k) || newY < 0 || newY > 3 || newX < 0 || newX > 3) {
			Vec[i].d += 1;
			if (Vec[i].d == 9) Vec[i].d = 1;
			cnt++;
		}
		else {
			int tmp = board[newY][newX];
			board[newY][newX] = i + 1;
			board[hang][yal] = tmp;
			checkflag = true;
		}
		if (checkflag || cnt >= 8) break;
	}
}


void DFS(int sum, int sharkD, int hang, int yal) {
	int tmp_board[6][6];

	if (result < sum) {
		result = sum;
	}
	for (int i = 1; i <= 16; i++) {
		if (Vec[i - 1].flag == true) continue;
		bool flag = false;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (board[j][k] == i) {
					flag = true;
					changeArea(i - 1, j, k, hang, yal);
					break;
				}
			}
			if (flag) break;
		}
	}
	memcpy(tmp_board, board, sizeof(tmp_board));
	vector<pos> tmp_Vec;
	for (int i = 0; i < Vec.size(); i++) {
		tmp_Vec.push_back(pos({ Vec[i].n, Vec[i].d, Vec[i].flag }));
	}
	while (1) {
		int newY = hang + dirY[sharkD];
		int newX = yal + dirX[sharkD];
		if (newY < 0 || newY > 3 || newX < 0 || newX > 3) {
			break;
		}

		if (Vec[board[newY][newX] - 1].flag) {
			hang = newY, yal = newX;
		}

		else if (!Vec[board[newY][newX] - 1].flag) {
			Vec[board[newY][newX] - 1].flag = true;

			DFS(sum + Vec[board[newY][newX] - 1].n, Vec[board[newY][newX] - 1].d, newY, newX);

			memcpy(board, tmp_board, sizeof(tmp_board));

			Vec.clear();
			for (int i = 0; i < tmp_Vec.size(); i++) {
				Vec.push_back(tmp_Vec[i]);
			}

			hang = newY, yal = newX;
		}
	}
}
