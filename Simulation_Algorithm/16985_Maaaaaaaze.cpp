#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int board[4][5][5][5];
int tmpBoard[5][5][5]; // board를 가지고 미로를 만든 board
bool check[5][5][5];
int dirY[6] = { -1, 1, 0 ,0, 0, 0 };
int dirX[6] = { 0, 0, -1, 1, 0 ,0 };
int dirZ[6] = { 0, 0, 0, 0, -1, 1 };
int tmp[5]; // 몇도를 회전할 것인지 넣는 배열
int orders[5]; // 어떤 판을 어느 위치에 넣을 것인지 넣는 배열
bool ordersCheck[5];
int time, result; // time : 미로를 탈출하는 경우의 이동값, result : 최종 결과값
bool flag, onFlag; // flag : 미로를 탈출할 수 있는지 판단, onFlag : 모든 값이 1일경우 결과값이 12이므로 탈출..

typedef struct _pos {
	int h, y, z;
}pos;

void DFS(int depth);

int main() {
	//입력
	result = 987654321;
	for (int i = 0; i < 5; i++) {
		for (int hang = 0; hang < 5; hang++) {
			for (int yal = 0; yal < 5; yal++) {
				scanf("%d", &board[0][i][hang][yal]);
				if (board[0][i][hang][yal] == 0) onFlag = true;
			}
		}
	}
	// 보드회전값 넣기(0도, 90도, 180도, 270도)
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			for (int hang = 0; hang < 5; hang++) {
				for (int yal = 0; yal < 5; yal++) {
					board[i][j][hang][yal] = board[i - 1][j][yal][4 - hang];
				}
			}
		}
	}
	// 모든보드값이 1일 때 결과값 12..
	if (!onFlag) {
		printf("12\n");
		return 0;
	}

	DFS(0);
	//출력
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}
//미로탈출
void BFS() {
	check[0][0][0] = true;
	queue<pos> Q;
	time = 0;
	Q.push(pos({ 0, 0, 0 }));

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			if (p.h == 4 && p.y == 4 && p.z == 4) {
				flag = true;
				return;
			}
			for (int dir = 0; dir < 6; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				int newZ = p.z + dirZ[dir];

				if (newY < 0 || newY > 4 || newX < 0 || newX > 4 || newZ < 0 || newZ > 4) continue;

				if (tmpBoard[newZ][newY][newX] == 1 && !check[newZ][newY][newX]) {
					check[newZ][newY][newX] = true;
					Q.push(pos({ newY, newX, newZ }));
				}
			}
		}
		time++;
		if (time > result) return;
	}
}
// 회전한 5개 각각의 보드를 어느 위치에 저장시킬지 orders 배열에 넣는다..
void DFS1(int depth) {
	if (depth == 5) {
		//초기화
		memset(check, false, sizeof(check));
		flag = false;
		//tmpBoard에 미로를 만든다..
		for (int i = 0; i < 5; i++) {
			for (int hang = 0; hang < 5; hang++) {
				for (int yal = 0; yal < 5; yal++) {
					tmpBoard[i][hang][yal] = board[tmp[i]][orders[i]][hang][yal];
				}
			}
		}
		//출발지점과 끝나는 지점이 이동할 수 있는 경우라면 BFS를 통해 미로이동
		if (tmpBoard[0][0][0] == 1 && tmpBoard[4][4][4] == 1) BFS();
		// 미로를 탈출했다면 결과값 갱신..
		if (flag) {
			if (result > time) result = time;
			return;
		}
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (!ordersCheck[i]) {
			ordersCheck[i] = true;
			orders[depth] = i;
			DFS1(depth + 1);
			orders[depth] = 0;
			ordersCheck[i] = false;
		}
	}
}
// 5개 각각의 보드를 얼마나 회전할 것인지 tmp에 넣는다
void DFS(int depth) {
	if (depth == 5) {
		DFS1(0);
		return;
	}
	for (int i = 0; i < 4; i++) {
		tmp[depth] = i;
		DFS(depth + 1);
		tmp[depth] = 0;
	}
}