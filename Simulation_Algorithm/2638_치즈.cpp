#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int board[101][101];
int checkNum[101][101];
bool check[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int chezz;
int result;

typedef struct _pos {
	int h, y;
}pos;

void BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) chezz++; // 치즈의 크기 증가..
		}
	}
	while (1) {
		BFS(0, 0); // 외부공기를 체크..
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (board[hang][yal] == 1) { // 치즈이면
					int cnt = 0;
					for (int dir = 0; dir < 4; dir++) { // 상하좌우를보고
						int newY = hang + dirY[dir];
						int newX = yal + dirX[dir];

						if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

						if (check[newY][newX] == 1) { // 외부공기와 만나면
							cnt++; // cnt 증가
							if (cnt == 2) { // 외부공기를 2번이상 만나면
								board[hang][yal] = 0; // 치즈를 녹인다..
								chezz--;
								break;
							}
						}
					}
				}
			}
		}
		result++; // 결과값 갱신..
		if(chezz == 0) break; // 치즈가 모두 녹으면 break;
		memset(check, false, sizeof(check)); // 외부공기 초기화..
	}
	printf("%d\n", result);
	return 0;
}
// 외부공기체크..
void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}