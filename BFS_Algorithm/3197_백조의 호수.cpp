#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
char str[1501];
char board[1501][1501];
bool check[1501][1501];
int waterBoard[1501][1501]; // 섬이 몇초에 없어지는지 체크하는 배열
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, time;
}pos;
vector<pos> swan; // 백조 2마리가 들어가있는다.

struct cmp {
	bool operator() (pos p, pos q) {
		return p.time > q.time;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;
queue<pos> times;

int BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'L') {
				swan.push_back(pos({ hang, yal, 0}));
				board[hang][yal] = '.';
				times.push(pos({ hang, yal, 0 })); // 바다를 time queue에 넣는다
				check[hang][yal] = true;
			}
			else if (board[hang][yal] == '.') {
				times.push(pos({ hang, yal, 0 }));// 바다를 time queue에 넣는다
				check[hang][yal] = true;
			}
		}
	}
	int time = 1;
	while (!times.empty()) {
		int sz = times.size();
		for (int s = 0; s < sz; s++) {
			pos p = times.front();
			times.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// 섬이 언제 녹는지 queue를 돌면서 waterBoard에 체크한다..
				if (board[newY][newX] == 'X' && !check[newY][newX]) {
					check[newY][newX] = true;
					waterBoard[newY][newX] = time;
					times.push(pos({ newY, newX }));
				}
			}
		}
		time++;
	}
	
	memset(check, false, sizeof(check)); // 초기화
	printf("%d\n",BFS(swan[0].h, swan[0].y)); // 출력
	return 0;
}

// 백조가 만나는 시간을 체크하는 BFS
int BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		if (p.h == swan[1].h && p.y == swan[1].y) return p.time;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (!check[newY][newX]) {
				check[newY][newX] = true;
				if (p.time >= waterBoard[newY][newX]) {
					Q.push(pos({ newY, newX, p.time }));
				}
				else {
					Q.push(pos({ newY, newX, waterBoard[newY][newX] }));
				}
			}
		}
	}
}
