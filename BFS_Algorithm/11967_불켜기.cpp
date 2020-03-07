/*
	N * N헛간에서 어둠을 무서워하는 암소 베시는 최대한 많은 방에 불을 밝히고 싶어한다.
	베시는 유일하게 불이 켜져있는 방인(1,1)방에서 출발하고 어떤 방에는 다른방의 불을 끄고 켤 수 있는 스위치가 달려있다.
	베시는 불이 켜져있는 방으로만 들어갈 수 있고, 각 방에서는 상하좌우에 인접한 방으로 움직일 수 있다.
	최대한 많은 방의 불을 킬 수 있는 알고리즘을 구현..

	(1,1)방에들어가서 불을 켜고 방문했던 곳을 리셋시키고 다시 (1,1)부터 시작하여 들어갈 수 있는 방을 찾고
	그곳에서 불을 킬 수 있는 곳을 또키고 리셋시키고 들어갈 수 있는 곳을 찾으면서 알고리즘을 구현..

	
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
bool check[101][101]; // 불을 켰는지 판단하는 check배열
bool visited_check[101][101];// 방문한 곳인지 판단하는 visited_check배열..
int result;
int main_result;
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec[101][101]; // (x, y)에서 불을 켤 수 있는 헛간을 저장하는 Vector..
queue<pos> Q; // 방문할 수있는 곳을 저장하기 위한 Q..

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int x, y, a, b, i = 0; i < M; i++) {
		scanf("%d %d %d %d", &x, &y, &a, &b);
		Vec[x][y].push_back(pos({ a, b }));
	}

	Q.push(pos({ 1, 1 })); // 맨 처음 헛간에 불이 켜진 1, 1을 방문..
	check[1][1] = true; // 1, 1헛간에 불을 킨다..
	result = 1;

	while (!Q.empty()) {
		int sz = Q.size();

		for (int s = 0; s < sz; s++) { // 방문할 수 있는 헛간에서 불이 안켜져있는 헛간에 불을 킨다..
			pos p = Q.front();
			Q.pop();

			int Vsz = Vec[p.h][p.y].size();

			for (int s1 = 0; s1 < Vsz; s1++) {
				int first = Vec[p.h][p.y][s1].h;
				int second = Vec[p.h][p.y][s1].y;

				if (!check[first][second]) {
					check[first][second] = true;
					result++;
				}
			}

		}

		if (main_result == result) break; // 더이상 불을 킬 수 없으면 while 문을 빠져나오고
		else main_result = result; // 아니면 값을 갱신하고 while문을 돈다..

		memset(visited_check, false, sizeof(visited_check)); // 방문했던 곳을 리셋시키고
		BFS(1, 1); // BFS를 통해서 1, 1에서 상하좌우를 살피면서 방문할 수 있는 불이 켜진곳을 곳을 Q에 넣는다....
	}
	printf("%d\n", result);

	return 0;
}


void BFS(int hang, int yal) {
	visited_check[hang][yal] = true;
	queue<pos> re_Q;
	re_Q.push(pos({ hang, yal}));

	while (!re_Q.empty()) {
		pos p = re_Q.front();
		re_Q.pop();
		Q.push(pos({ p.h, p.y }));

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

			if (!visited_check[newY][newX] && check[newY][newX]) {
				re_Q.push(pos({ newY, newX }));
				visited_check[newY][newX] = true;
			}
		}
	}
}