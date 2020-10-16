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
vector<pos> Vec[2]; // 구슬의 처음 위치 저장..

void DFS(int depth, int dir, int rh, int ry, int bh, int by, bool rf, bool bf);

int main() {
	//입력
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
	 // depth : 이동한 횟수 , dir : 현재 이동할 방향, rh, ry : 빨간구슬위치 bh, by : 파란구슬위치, rf : 빨간구슬이 구멍에 빠졌는지, bf 파란구슬이 구멍에 빠졌는지
	DFS(0, -1, Vec[0][0].h, Vec[0][0].y, Vec[1][0].h, Vec[1][0].y, false, false);
	//출력
	if (!checkFlag) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}


void DFS(int depth, int dir, int rh, int ry, int bh, int by, bool rf, bool bf) {
	if (result <= depth) return; // 결과값보다 이동횟수가 많으면 return..
	char tmpBoard[11][11]; // 각 재귀마다복사하기 위해..

	if (depth > 0 && depth <= 10) { // 이동횟수가 1~10 이하라면
		bool Rflag = false, Bflag = false;
		// 빨간 파란구슬 이동
		while (1) {
			if (!Rflag) {
				board[rh][ry] = '.';
				rh += dirY[dir], ry += dirX[dir];
				// 파란구슬을 만났을 때는 다시 그자리로 간다
				if (board[rh][ry] == 'B') {
					rh -= dirY[dir], ry -= dirX[dir];
					board[rh][ry] = 'R';
					if (Bflag) Rflag = true; // 만약 파란구슬이 벽에 닿아서 멈췄다면 레드도 멈춘다.
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
		// 결과값을 뽑을 수 있는 경우
		if (rf && !bf) {
			checkFlag = true; // 결과값이 한번나왔으므로 일단 true
			if (result > depth) result = depth; // 결과값 갱신..
			return;
		}
		// 결과값이 나올 수 없는 경우이므로 return..
		if ((!rf && bf) || (rf && bf)) return;
		if (depth == 10) return;
	}
	// board를 tmpBoard에 복사해서 재귀함수가 돌아올때 board를 사용
	for (int i = 0; i < 4; i++) {
		memcpy(tmpBoard, board, sizeof(tmpBoard));
		if (dir != i) DFS(depth + 1, i, rh, ry, bh, by, false, false);
		memcpy(board, tmpBoard, sizeof(board));
	}
}