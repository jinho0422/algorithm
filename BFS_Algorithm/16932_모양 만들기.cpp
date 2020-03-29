/*
	https://www.acmicpc.net/problem/16932
	배열의 각 칸에는 0과 1 중의 하나가 들어있다. 두 칸이 서로 변을 공유할 때, 두 칸을 인접한다고 한다.
	배열의 칸 하나에 들어있는 수를 변경해서 인접한 1이 가장 큰 알고리즘을 구현.

	1이 뭉쳐있는 각각을 BFS를 통해 섬 번호를 매겨 2차원 배열의 0에서 상하좌우를 봤을 때 섬이 있을 경우 결과값에
	더하면서 가장 큰 면적을 찾는 알고리즘 구현..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[1001][1001];
bool check[1001][1001];
bool checkNumber[10000001];// 0에서 상하좌우를 보고 섬이 있으면 방문 체크..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int island;
int islandSize[10000001]; // 섬 각각의 크기를 넣는 배열..
int result; // 0에서의  상하좌우를 더한 결과값
int maxresult; // 0에서 상화좌우를 더한 최대 결과값을 뽑기위해..

typedef struct _pos { // 행열을 넣는 struct..
	int h, y;
}pos;

queue<int> QQ; // 0에서 섬이 연결되는 곳을 넣어주어 방문체크를 풀기위한 queue
void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	island = 1;

	for (int hang = 0; hang < N; hang++) { // 섬번호 매기기..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal);
				island++;
			}
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0) { // 만약 0이라면
				result = 0;
				for (int dir = 0; dir < 4; dir++) {// 상하좌우를 보고
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];

					if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

					if (board[newY][newX] != 0 && !checkNumber[board[newY][newX]]) { // 섬이있고 방문한 섬이 아니라면
						result += islandSize[board[newY][newX]]; // 섬의 크기를 더해주고
						checkNumber[board[newY][newX]] = true;
						QQ.push(board[newY][newX]); // 들어간 섬 방문체크 넣어주는 queue
					}
				}
				int sz = QQ.size();
				for (int s = 0; s < sz; s++) { // 방문햇던 섬의 방문체크를 풀어주는 것.. (시간초과를 막기위해..)
					int p = QQ.front();
					QQ.pop();
					checkNumber[p] = false;
				}

			}
			if (maxresult < result) maxresult = result;
		}
	}
	printf("%d\n", maxresult + 1);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	board[hang][yal] = island;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));
	int num = 1;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = island;
				num++; // 섬의 크기++;
				Q.push(pos({ newY, newX }));
			}
		}
	}
	islandSize[island] = num; // 각각의 섬의 크기 넣어주기..
}