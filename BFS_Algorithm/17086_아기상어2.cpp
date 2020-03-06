/*
	N*M크기의 공간에 아기 상어가 여러마리 있다. 격자판에 아기상어가 있는 곳은 1, 없는 곳은 0이다.
	아기상어가 없는 격자판에서 아기상어와 상,하, 좌, 우, 대각선으로 아기상어가 떨어져있는 안전거리의 최대값을 구하는 알고리즘

	격자판에서 아기상어가 없는곳에서 BFS를 이용하여 거리를 체크하면서 최대의 거리를 갱신하는 알고리즘 구현..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int board[50][50];
bool check[50][50];
int dirY[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };//상,하,좌,우,대각선
int dirX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int result;

typedef struct _pos {
	int h, y;
}pos;

int BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0) {//격자판에서 상어가 없는 곳..
				int length = BFS(hang, yal);// BFS를 통해 안전거리를 구함..
				if (result < length) result = length;//안전거리 최대값 갱신..
				memset(check, false, sizeof(check));// BFS를 사용할 때 visited를 하기 위해 check배열 리셋..
			}
		}
	}
	printf("%d\n", result);

	return 0;
}

int BFS(int hang, int yal) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int time = 0;

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			if (board[p.h][p.y] == 1) return time;//상어를 만나면 return 거리..

			for (int dir = 0; dir < 8; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;//격자판을 벗어나면 continue..

				if (board[newY][newX] == 0 && !check[newY][newX]) {// 안전한영역을 만낫을 때..
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
				if (board[newY][newX] == 1 && !check[newY][newX]) {//상어를 만났을 때..
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
			}
		}
		time++;// Q크기를 모두 돌면 거리증가..
	}
}