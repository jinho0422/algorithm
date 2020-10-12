#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, C;
int board[102][102];
int dirY[5] = { 0, -1, 1, 0, 0 };
int dirX[5] = { 0, 0, 0, 1, -1 }; // 위, 아래, 오른쪽, 왼쪽
int result;

typedef struct _pos {
	int h, y, v, dr, w; // h : hang, y : yal, v : 속도, dr : 뱡향, w : 크기
	bool flag;
}pos;
vector<pos> Vec[100001];

typedef struct _pos1 {
	int n, big; // n : 상어의 번호, big : 상어의 크기
}pos1;
struct cmp {
	bool operator() (pos1 p, pos1 q) {
		return p.big < q.big;
	}
};
priority_queue<pos1, vector<pos1>, cmp> Q[101][101];

void search(int yal);
void move();

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &C);
	for (int r, c, s, d, z, i = 1; i <= C; i++) {
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		board[r][c] = i;
		Vec[i].push_back(pos({ r, c, s, d, z }));
	}
	for (int yal = 1; yal <= M; yal++) {
		//사람이 열을 옮기면서 상어를 잡는 함수
		search(yal);
		// 상어를 움직인다..
		move();
	}
	printf("%d\n", result);
	return 0;
}

void search(int yal) {
	for (int hang = 1; hang <= N; hang++) {
		if (board[hang][yal] != 0) {
			Vec[board[hang][yal]][0].flag = true;
			result += Vec[board[hang][yal]][0].w;
			return;
		}
	}
}
void move() {
	memset(board, 0, sizeof(board));
	for (int i = 1; i <= C; i++) {
		if (Vec[i][0].flag) continue; // 없어진 상어는 continue..
		int first = 0;
		 //상하움직임..
		if (Vec[i][0].dr == 1 || Vec[i][0].dr == 2) {
			first = Vec[i][0].v % ((N - 1) * 2); // 속도의 나머지값으로 움직인다.
			int sh = Vec[i][0].h, sy = Vec[i][0].y;
			for (int j = 0; j < first;) {
				int newY = sh + dirY[Vec[i][0].dr];
				int newX = sy + dirX[Vec[i][0].dr];

				if (newY <= 0 || newY > N) {
					if (Vec[i][0].dr == 1) Vec[i][0].dr += 1; //위로올라갈 때 방향을 아래로 바꾸기..
					else Vec[i][0].dr -= 1; // 아래로내려갈때 위로 방향바꾸기..
					continue;
				}
				sh = newY, sy = newX;
				j++;
			}
			Vec[i][0].h = sh, Vec[i][0].y = sy;
			Q[sh][sy].push(pos1({ i, Vec[i][0].w }));
		}
		//좌우움직임..
		else if (Vec[i][0].dr == 3 || Vec[i][0].dr == 4) {
			first = Vec[i][0].v % ((M - 1) * 2);
			int sh = Vec[i][0].h, sy = Vec[i][0].y;
			for (int j = 0; j < first;) {
				int newY = sh + dirY[Vec[i][0].dr];
				int newX = sy + dirX[Vec[i][0].dr];

				if (newX <= 0 || newX > M) {
					if (Vec[i][0].dr == 3) Vec[i][0].dr += 1; // 우로가고있을 때 좌로 방향바꾸기
					else Vec[i][0].dr -= 1; // 좌로가고있을 때 우로 방향바꾸기..
					continue;
				}
				sh = newY, sy = newX;
				j++;
			}
			Vec[i][0].h = sh, Vec[i][0].y = sy;
			Q[sh][sy].push(pos1({ i, Vec[i][0].w })); // 상어 움직이고 모이기..
		}
	}
	// 모인상어중 가장 크기가 큰 상어를 놔두고 나머지는 죽인다..
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			if (Q[hang][yal].size() == 0) continue;
			pos1 p = Q[hang][yal].top();
			board[Vec[p.n][0].h][Vec[p.n][0].y] = p.n;
			Q[hang][yal].pop();
			while (!Q[hang][yal].empty()) {
				p = Q[hang][yal].top();
				Vec[p.n][0].flag = true;
				Q[hang][yal].pop();
			}
		}
	}
}