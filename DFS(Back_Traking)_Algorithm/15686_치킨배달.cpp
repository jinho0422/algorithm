#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N, M;
int board[51][51];
int check[14];
int result;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> home; // 집의 좌표를 넣는 vector
vector<pos> chicken; // 치킨집의 좌표를넣는 vector

void DFS(int depth, int start);

int main() {
	//입력
	result = 214700000;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) home.push_back(pos({ hang, yal }));
			if (board[hang][yal] == 2) chicken.push_back(pos({ hang, yal }));
		}
	}
	DFS(0, 0);
	printf("%d\n", result);
	return 0;
}
void DFS(int depth, int start) {
	//만약 원하는 치킨집의 갯수를 고르면
	if (depth == M) {
		int movesum = 0; // 집에서 치킨집거리의 최소를 모두 더한 값
		// 하나의 치킨집에서 모든 집을 다 돌면서 최소의 거리를 찾아서 movemin갱신
		for (int i = 0; i < home.size(); i++) {
			int movemin = 214700000; // 집에서 최소의 거리에 있는 치킨집 거리
			for (int j = 0; j < depth; j++) {
				int chH = chicken[check[j]].h;
				int chY = chicken[check[j]].y;

				int move = abs(home[i].h - chH) + abs(home[i].y - chY);
				if (movemin > move) movemin = move;
			}
			movesum += movemin;
		}
		// 치킨집중에 선택해서 고른곳 중 모든 집이 가장 적은 거리에 있는 치킨집의 최종 거리 갱신
		if (result > movesum) result = movesum;
		return;
	}
	for (int i = start; i < chicken.size(); i++) {
		check[depth] = i;
		DFS(depth + 1, i + 1);
		check[depth] = 0;
	}
}