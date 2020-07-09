#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, M, T;
int board[101][101];
bool check[2][101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;
typedef struct _pos {
	int h, y, cnt, flag; // 행, 열, 간 거리, 검을 획득했는지 안했는지..
}pos;

queue<pos> Q;

void solve(int hang, int yal, int go);

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &T);
	result = INF;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	//BFS 탐색을 위해..
	solve(0, 0, 0);
	if (result > T) printf("Fail\n");
	else printf("%d\n", result);
	return 0;
}
void solve(int hang, int yal, int go) {
	check[0][0][0] = true;
	Q.push(pos({ hang, yal, go, 0 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		// 공주님에게 도착했으면, 결과값 갱신..
		if (p.h == N - 1 && p.y == M - 1) {
			if (result > p.cnt) result = p.cnt;
			continue;
		}
		//결과값보다 이동거리가 많다면 continue..
		if (p.cnt > result) continue;
		//아직 검을 획득하지 못했다면..
		if (p.flag == 0) {
			//상하좌우를 보고
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// 갈 수 있는 곳이면 가고
				if (board[newY][newX] == 0 && !check[0][newY][newX]) {
					check[0][newY][newX] = true;
					Q.push(pos({ newY, newX,p.cnt + 1, 0 }));
				}
				//검을 획득할 수 있으면 p.flag를 1로 만든다..
				if (board[newY][newX] == 2 && !check[0][newY][newX]) {
					check[0][newY][newX] = true;
					check[1][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt + 1, 1 }));
				}
			}
		}
		//검을 가지고 있으면 검을 가지고 있는 check[1][hang][yal]에서 visited를 체크하며 움직인다.
		else {
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (!check[1][newY][newX]) {
					check[1][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt + 1, 1 }));
				}
			}
		}
	}
}