#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
char str[11];
char board[11][11];
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, -1, 0, 1 };
int tmpdir[10];
bool checkFlag;
int result;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec[2]; // ������ ó�� ��ġ ����..

void DFS(int depth, int dir, int rh, int ry, int bh, int by, bool rf, bool bf);

int main() {
	//�Է�
	result = 100;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'R') {
				Vec[0].push_back(pos({ hang, yal}));
			}
			if (board[hang][yal] == 'B') {
				Vec[1].push_back(pos({ hang, yal}));
			}
		}
	}
	 // depth : �̵��� Ƚ�� , dir : ���� �̵��� ����, rh, ry : ����������ġ bh, by : �Ķ�������ġ, rf : ���������� ���ۿ� ��������, bf �Ķ������� ���ۿ� ��������
	DFS(0, -1, Vec[0][0].h, Vec[0][0].y, Vec[1][0].h, Vec[1][0].y, false, false);
	//���
	if (!checkFlag) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}


void DFS(int depth, int dir, int rh, int ry, int bh, int by, bool rf, bool bf) {
	if (result <= depth) return; // ��������� �̵�Ƚ���� ������ return..
	char tmpBoard[11][11]; // �� ��͸��ٺ����ϱ� ����..

	if (depth > 0 && depth <= 10) { // �̵�Ƚ���� 1~10 ���϶��
		bool Rflag = false, Bflag = false;
		// ���� �Ķ����� �̵�
		while (1) {
			if (!Rflag) {
				board[rh][ry] = '.';
				rh += dirY[dir], ry += dirX[dir];
				// �Ķ������� ������ ���� �ٽ� ���ڸ��� ����
				if (board[rh][ry] == 'B') {
					rh -= dirY[dir], ry -= dirX[dir];
					board[rh][ry] = 'R';
					if (Bflag) Rflag = true; // ���� �Ķ������� ���� ��Ƽ� ����ٸ� ���嵵 �����.
				}
				else if (board[rh][ry] == '.') board[rh][ry] = 'R';
				else if (board[rh][ry] == 'O') {
					rf = true;
					Rflag = true;
				}
				else if (board[rh][ry] == '#') {
					rh -= dirY[dir], ry -= dirX[dir];
					board[rh][ry] = 'R';
					Rflag = true;
				}
			}

			if (!Bflag) {
				board[bh][by] = '.';
				bh += dirY[dir], by += dirX[dir];
				if (board[bh][by] == 'R') {

					bh -= dirY[dir], by -= dirX[dir];
					board[bh][by] = 'B';
					if (Rflag) Bflag = true;
				}
				else if (board[bh][by] == '.') board[bh][by] = 'B';
				else if (board[bh][by] == 'O') {
					bf = true;
					Bflag = true;
				}
				else if (board[bh][by] == '#') {
					bh -= dirY[dir], by -= dirX[dir];
					board[bh][by] = 'B';
					Bflag = true;
				}
			}
			if (Rflag && Bflag) break;
		}
		// ������� ���� �� �ִ� ���
		if (rf && !bf) {
			checkFlag = true; // ������� �ѹ��������Ƿ� �ϴ� true
			if (result > depth) result = depth; // ����� ����..
			return;
		}
		// ������� ���� �� ���� ����̹Ƿ� return..
		if ((!rf && bf) || (rf && bf)) return;
		if (depth == 10) return;
	}
	// board�� tmpBoard�� �����ؼ� ����Լ��� ���ƿö� board�� ���
	for (int i = 0; i < 4; i++) {
		memcpy(tmpBoard, board, sizeof(tmpBoard));
		if (dir != i) DFS(depth + 1, i, rh, ry, bh, by, false, false);
		memcpy(board, tmpBoard, sizeof(board));
	}
}