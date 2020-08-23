#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>

using namespace std;

int N, L, R;
int board[51][51];
int tmpboard[51][51]; // 모든 국가를 판단 후 인구 이동이 끝났을 때의 인구모습
bool check[51][51]; // 국가 방문 체크..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int resultTime;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // 인구이동이 가능한 국가를 모은 vector
queue<pos> Q; 

int BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d %d", &N, &L, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	while (1) {
		bool moveCheck = false; // 인구이동이 일어나는지 판단하는 check..
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if (!check[hang][yal]) { // 모든 국가를 보는 중 아직 보지 않은 국가가 있다면..
					int sum = BFS(hang, yal); // 인구이동이 가능한지 판단 할 수 있는 함수..
					int sz = Vec.size();
					if (sz>= 2) moveCheck = true; // 만약 Vector크기가 2이상이면 국가 중 인구가 움직일 수 있다 판단..
					for (int i = 0; i < sz; i++) { // 움직일 수 있는 국가 인구 전체를 평균내서 넣어준다..
						tmpboard[Vec[i].h][Vec[i].y] = sum / sz;
					}
					Vec.clear(); // 다음 움직일 수 있는 국가를 판단하기 위한 초기화..
				}
			}
		}
		if (!moveCheck) break; // 움직일 수 없으면 break..
		else {
			resultTime++; // 결과값 증가(움직일 수 있으면)
			memcpy(board, tmpboard, sizeof(tmpboard)); // tmpboard에 움직인 후의 인구 모습을 board에 복사..
			memset(check, false, sizeof(check)); // 국가 방문 체크 함수 초기화
		}
	}
	//출력
	printf("%d\n", resultTime);
	return 0;
}

int BFS(int hang, int yal) {
	int populationSum = 0; // 이동할 수 있는 모든 국가의 인구의 합
	check[hang][yal] = true; // 국가 방문 체크..
	Q.push(pos({ hang, yal }));
	Vec.push_back(pos({ hang, yal }));
	populationSum += board[hang][yal];
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N- 1) continue;
			// 국가가 움직일 수 있는지 판단해서 Vector에 넣는다..
			if ((abs(board[p.h][p.y] - board[newY][newX]) >= L) && (abs(board[p.h][p.y] - board[newY][newX]) <= R) && !check[newY][newX]) {
				check[newY][newX] = true;
				Vec.push_back(pos({ newY, newX }));
				Q.push(pos({ newY, newX }));
				populationSum += board[newY][newX];
			}
		}
	}
	return populationSum;
}