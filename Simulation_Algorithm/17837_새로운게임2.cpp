#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;

int N, M;
int board[14][14]; // 보드의 색깔을 보기위해 0 : 흰색, 1 : 빨간색, 2 : 파란색
int dirY[5] = {0, 0, 0, -1, 1 };
int dirX[5] = {0, 1, -1, 0, 0 };
int result;

typedef struct _pos {
	int h, y, d;
}pos;

deque<int> Q[14][14]; // 각각 행열 위치에 말이 몇개인지 보기 위해.. 
vector<pos> Vec[10]; // 말의 행,열, 방향넣는 vector

void white(int horse, int H, int Y, int nY, int nX);
void red(int horse, int H, int Y, int nY, int nX);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a][b].push_back(i);
		Vec[i].push_back(pos({ a, b, c }));
	}
	result = 1; // 결과값
	while (1) {
		for (int i = 0; i < M; i++) {
			//가야될 곳
			int newY = Vec[i][0].h + dirY[Vec[i][0].d];
			int newX = Vec[i][0].y + dirX[Vec[i][0].d];
			//가야될곳이 파란색이거나 경계값을 벗어나면
			if (newY <= 0 || newY > N  || newX <= 0 || newX > N || board[newY][newX] == 2) {
				//방향을 바꿔서
				if (Vec[i][0].d == 1 || Vec[i][0].d == 3) Vec[i][0].d++;
				else if (Vec[i][0].d == 2 || Vec[i][0].d == 4) Vec[i][0].d--;
				//가야될 곳을 보고
				newY = Vec[i][0].h + dirY[Vec[i][0].d];
				newX = Vec[i][0].y + dirX[Vec[i][0].d];
				// 다시 파란색이거나 경계값이면 continue
				if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 2) continue;
				// 흰색
				else if (board[newY][newX] == 0) white(i,Vec[i][0].h, Vec[i][0].y, newY, newX);
				// 빨간색
				else if (board[newY][newX] == 1) red(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			}
			//흰색
			else if (board[newY][newX] == 0) white(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			//빨간색
			else if (board[newY][newX] == 1) red(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			//말이 하나씩 이동하면서 한 구역에 4개이상모였는지 보고 결과값 출력
			for (int hang = 1; hang <= N; hang++) {
				for (int yal = 1; yal <= N; yal++) {
					if (Q[hang][yal].size() >= 4) {
						printf("%d\n", result);
						return 0;
					}
				}
			}
		}
		result++;
		if (result > 1000) break;	
	}
	printf("-1\n");
	return 0;;
}

void white(int horse, int H, int Y, int nY, int nX) {
	bool flag = false;
	int sz = Q[H][Y].size();
	for (int s = 0; s < sz; s++) {
		int p = Q[H][Y].front();
		Q[H][Y].pop_front();
		if (p == horse) flag = true;
		// 원하는 말이 나타나면 이동할 칸으로 다 이동
		if (flag) {	
			Q[nY][nX].push_back(p);
			Vec[p][0].h = nY, Vec[p][0].y = nX;
		}
		// 원하는 말이 나오기 전에는 위로쌓는다.
		else Q[H][Y].push_back(p);	
	}
}
void red(int horse, int H, int Y, int nY, int nX) {
	bool flag = false;
	stack<int> S;
	int sz = Q[H][Y].size();
	for (int s = 0; s < sz; s++) {
		int p = Q[H][Y].front();
		Q[H][Y].pop_front();
		if (p == horse) flag = true;
		// 원하는 말이 나타나면 stack에 저장
		if (flag) {
			S.push(p);
		}
		//원하는 말이 나오기 전에는 위로 쌓는다
		else Q[H][Y].push_back(p);
	}
	//뒤집어 넣기 위해..
	int Ssz = S.size();
	for (int i = 0; i < Ssz; i++) {
		int p = S.top();
		S.pop();
		Q[nY][nX].push_back(p);
		Vec[p][0].h = nY, Vec[p][0].y = nX;
	}
}
