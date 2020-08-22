#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int board[101][101];
bool check[101][101];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int cheeze;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // 공기의 좌표를 넣기위해..
queue<pos> Q; // 공기의 영역을 구하기 위해 ..

void air(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) cheeze++; // 치즈의 크기
		}
	}
	int timeResult = 0; // 시간결과값
	int meltcnt = 0; // 시간당 녹은 치즈의 크기
	while (1) {
		// 치즈가 다 녹으면 출력..
		if (cheeze == 0) {
			printf("%d\n%d\n", timeResult, meltcnt);
			break;
		}
		timeResult++;
		meltcnt = 0;
		air(0, 0);// 공기의 영역을 구하기위해..
		//공기의 영역을 돌아보며 주변에 치즈가 있으면 녹인다.,
		for (int s = 0; s < Vec.size(); s++) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[s].h + dirY[dir];
				int newX = Vec[s].y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] == 1) {
					meltcnt++;
					board[newY][newX] = 0;
				}
			}
		}
		// 현재의 치즈에서 녹은 치즈를 뺀다..
		cheeze -= meltcnt;
		//초기화
		Vec.clear();
		memset(check, false, sizeof(check));
	}
	return 0;
}

void air(int hang, int yal) {
	check[hang][yal] = true;
	Vec.push_back(pos({ hang, yal }));
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
				Vec.push_back(pos({ newY, newX }));
			}
		}
	}
}