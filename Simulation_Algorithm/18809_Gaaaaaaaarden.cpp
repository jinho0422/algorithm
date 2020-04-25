/*
	https://www.acmicpc.net/problem/18809
	배양액을 넣을 수 있는 곳중에 Green + Red 갯수를 뽑는 DFS,
	DFS로 뽑은 곳에서 Green을 넣을 곳 Red를 넣을 곳을 찾는 DFS,
	찾은 곳에서 각각 GQ, RG에 넣어 동시에 만나는 곳을 BFS로 찾는 알고리즘 구현.
*/



#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, M, G, R;
int board[50][50];
bool checkGreen[11]; // Green 배양액을 넣을지 Red 배양액을 넣을지 판단하는 check.
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

int checkFlower[50][50]; // 동시에 만날 수 있는지 판단하는 check.
bool Green[50][50]; // Green 배양액을 넣고 BFS 돌릴 check
bool Red[50][50]; // Red 배약액을 넣고 BFS 돌릴 check
int result;
int assume;

typedef struct _pos {
	int h, y;
}pos;
pos tmp[11];

vector<pos> Vec; // 배약액을 넣을 수 있는 곳을 넣는 vector
queue<pos> GQ; // Green배양액을 넣을 queue
queue<pos> RQ; // Red배양액을 넣을 Red

void solve_DFS(int depth, int start);

int main() {
	scanf("%d %d %d %d", &N, &M, &G, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal })); // board == 2 배양액을 넣을 수 있는 곳으로 vector에 넣어준다.
		}
	}
	solve_DFS(0, 0); // 배양액을 넣을 수 있는 곳 중에 Green, Red 전체 배양액을 넣을 곳을 찾는 DFS 
	printf("%d\n",result);
	return 0;
}

void BFS(int num) {
	assume = 0;
	while (!RQ.empty() || !GQ.empty()) {
		//Green 배양액을 먼저 돌리면서 
		int Gsz = GQ.size();
		for (int s = 0; s < Gsz; s++) {
			pos p = GQ.front();
			GQ.pop();
			if (Red[p.h][p.y]) continue; // 다음으로 가기전에 꽃이 된 곳이면 continue..

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// board가 호수가 아니고  Green, Red 모두 방문한 적도 없는 곳이면..
				if (board[newY][newX] != 0 && !Green[newY][newX] && !Red[newY][newX] && checkFlower[newY][newX] == 0) {
					Green[newY][newX] = true;
					checkFlower[newY][newX] = num; // 몇분에 방문한 곳인지 체크를 해논다..
					GQ.push(pos({ newY, newX }));
				}
			}
		}
		// 그 후, Red 배양액을 돌리면서
		int Rsz = RQ.size();
		for (int s = 0; s < Rsz; s++) {
			pos p = RQ.front();
			RQ.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// 같은 시간에 방문한 곳이면 assume을++를 해주어 꽃이 핀곳을 판단..
				if (board[newY][newX] != 0 && !Red[newY][newX]) {
					if (Green[newY][newX] && checkFlower[newY][newX] == num) {
						Red[newY][newX] = true;
						assume++;
					}
					//아니면 RQ에 넣어준다..
					if (!Green[newY][newX] && checkFlower[newY][newX] != num) {
						Red[newY][newX] = true;
						RQ.push(pos({ newY, newX }));
					}
				}
			}
		}
		num++; // Green과 Red가 모두 돌면 시간의 흐름을 넣어준다.
	}
	//결과값 갱신..
	if (result < assume) result = assume;
}

void DFS(int depth, int start) {

	if (depth == G) {
		// Green배양액과 Red배양액을 checkGreen을 통하여 분리하여 넣는다.
		for (int s = 0; s < G + R; s++) {
			if (checkGreen[s]) {
				Green[tmp[s].h][tmp[s].y] = true;
				GQ.push(pos({ tmp[s].h, tmp[s].y }));
			}
			else {
				Red[tmp[s].h][tmp[s].y] = true;
				RQ.push(pos({ tmp[s].h, tmp[s].y }));
			}
		}
		BFS(1);
		// 초기화..
		memset(Green, false, sizeof(Green));
		memset(Red, false, sizeof(Red));
		memset(checkFlower, 0, sizeof(checkFlower));
		while (!RQ.empty()) RQ.pop();
		while (!GQ.empty()) GQ.pop();
		return;
	}

	for (int s = start; s < G + R; s++) {
		checkGreen[s] = true;
		DFS(depth + 1, s + 1);
		checkGreen[s] = false;
	}
}

void solve_DFS(int depth, int start) {
	if (depth == G + R) {
		DFS(0, 0); // Green, Red를 넣을 board에서 Green을 어디에 넣을지 Red를 어디에 넣을지 찾는 DFS
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		tmp[depth] = { Vec[s].h, Vec[s].y };
		solve_DFS(depth + 1, s + 1);
	}
}