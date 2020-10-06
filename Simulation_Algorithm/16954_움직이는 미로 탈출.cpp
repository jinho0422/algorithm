#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

char str[9];
char board[9][9];
int dirY[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[9] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };
int wallCnt;

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;
int BFS(int hang, int yal);

int main() {
	//입력
	for (int hang = 0; hang < 8; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < 8; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '#') wallCnt++;
		}
	}
	//출력
	printf("%d\n", BFS(7, 0));
	return 0;
}

int BFS(int hang, int yal) {

	Q.push(pos({ hang, yal })); // 초기값 hang : 7, yal : 0

	while (!Q.empty()) {
		if (wallCnt == 0) return 1; // 벽이 없지만 Q의 크기가 0이 아닌경우는 움직일 수 있으므로
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 9; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				// 경계값과 움직일려고 하는 위치의 위쪽이 벽이면 넘어간다..
				if (newY < 0 || newY > 7 || newX < 0 || newX > 7 || board[newY - 1][newX] == '#') continue;

				if (board[newY][newX] == '.') {
					Q.push(pos({ newY, newX }));
				}
			}
		}
		// 벽이동
		for (int yal = 0; yal < 8; yal++) {
			for (int hang = 7; hang >= 0; hang--) {
				if (board[hang][yal] == '#') {
					if (hang == 7) {
						board[hang][yal] = '.';
						continue;
					}				
					board[hang + 1][yal] = board[hang][yal];
					board[hang][yal] = '.';
				}
			}
		}
		wallCnt = 0;
		//벽 세기
		for (int hang = 0; hang < 8; hang++) {
			for (int yal = 0; yal < 8; yal++) {
				if (board[hang][yal] == '#') wallCnt++;
			}
		}
	}
	return 0;
}