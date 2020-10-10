#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[51][51];
bool check[51][51];
int tmpBoard[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int zero, tmpZero;
int time, result;


typedef struct _pos {
	int h, y; //h : hang, y : yal, f : 활성바이러스인지 체크..
	bool f;
}pos;
queue<pos> Q;
vector<pos> Vec;

void DFS(int depth, int start);

int main() {
	//입력
	result = 987654321;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal, false }));// 바이러스이면 vector에 넣는다.		
			else if (board[hang][yal] == 0) zero++; // 0인곳이몇개인지 체크..
		}
	}
	//만약 0인곳이 없으면 0 출력..
	if (zero == 0) {
		printf("0\n");
		return 0;
	}
	DFS(0, 0);
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}
// 바이러스 확산시킨다.
void BFS() {
	// 활성바이러스를 Q에 넣는다.
	for (int s = 0; s < Vec.size(); s++) {
		if (Vec[s].f) {
			Q.push(pos({ Vec[s].h, Vec[s].y }));
			check[Vec[s].h][Vec[s].y] = true;
		}
	}
	time = 0;
	while (!Q.empty()) {
		if (time >= result) return; // 결과값보다 크면 리턴..
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// 0인 구역
				if (tmpBoard[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					tmpZero--;
				}
				// 비활성 구역..
				if (tmpBoard[newY][newX] == 2 && !check[newY][newX]) {
					Q.push(pos({ newY, newX }));
					check[newY][newX] = true;
				}
			}
		}
		time++;	
		if (tmpZero == 0) return;
	}
}
// 비활성 바이러스중에 M개를 활성바이러스로 만든다..
void DFS(int depth, int start) {
	if (depth == M) {
		//초기화
		while (!Q.empty()) Q.pop();
		memset( check, false, sizeof(check));
		memcpy(tmpBoard, board, sizeof(tmpBoard));
		tmpZero = zero;
		BFS();
		// 모든곳을 채웠다면..
		if (tmpZero == 0) {
			if (result > time) result = time;
		}
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		if (!Vec[s].f) {
			Vec[s].f = true;
			DFS(depth + 1, s + 1);
			Vec[s].f = false;
		}
	}
}