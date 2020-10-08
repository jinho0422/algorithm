#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M, G, R;
int board[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool check[10]; // 배양할 수 잇는 곳을 골랐을 때 그린을 심을지 레드를 심을지 판단..
int checkG[51][51]; // 그린 배약액이 몇분에 심었는지 파악하는 배열
int checkR[51][51]; // 레드 배양액이 몇분에 심었는지 파악하는 배열
bool checkMade[51][51]; // 같은 시간에 그린, 레드 배양액이 들어와 꽃이 된 경우를 판단..
int time, made, result; // time : 각각의 배양액이 이동한 시간, made : 꽃이 된 경우 세기 : result : 최종 결과값

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec; // 배양할 수 있는 장소..
pos seed[11];

queue<pos> Gr; // 그린 배양액
queue<pos> Re; // 레드 배양액

void DFS(int depth, int start);

int main() {
	//입력
	scanf("%d %d %d %d", &N, &M, &G, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal })); // 배양액을 넣을 수 있는 곳이면 Vec에 넣는다
		}
	}
	DFS(0, 0);
	//출력
	printf("%d\n", result);
	return 0;
}

void BFS() {
	time = 2; // 배양액이 이동한 시간..
	while (!Gr.empty() || !Re.empty()) {
		int Gsz = Gr.size();
		for (int s = 0; s < Gsz; s++) {
			pos p = Gr.front();
			Gr.pop();

			if (checkMade[p.h][p.y]) continue; // 꽃이 만들어진 경우는 continue..

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// 그린, 레드 배양액이 모두 안심어진곳으로 그린 배양액 먼저 이동..
				if (checkG[newY][newX] == 0 && checkR[newY][newX] == 0) {
					checkG[newY][newX] = time;
					Gr.push(pos({ newY, newX }));
				}
			}
		}
		int Rsz = Re.size();
		for (int s = 0; s < Rsz; s++) {
			pos p = Re.front();
			Re.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// 레드배양액도 가지않고 그린 배양액도 가지 않은 곳으로 이동
				if (checkR[newY][newX] == 0 && checkG[newY][newX] == 0) {
					checkR[newY][newX] = time;
					Re.push(pos({ newY, newX }));
				}
				//만약 레드배양액은 가지 않았찌만 그린 배양액이 같은 시간에 배양된 곳이라면 checkMade : true
				if (checkR[newY][newX] == 0 && checkG[newY][newX] == time) {
					checkMade[newY][newX] = true;
				}
			}
		}
		time++;
	}
}
// 뽑아낸 배양액을 심을 수 있는 곳중에 레드를 심을곳과 그린을 심을 곳을 check로 판단한다..
void DFS1(int depth, int start) {
	if (depth == G) {
		//초기화
		memset(checkR, 0, sizeof(checkR));
		memset(checkG, 0, sizeof(checkG));
		memset(checkMade, false, sizeof(checkMade));
		while (!Gr.empty()) Gr.pop();
		while (!Re.empty()) Re.pop();
		// check[i] : 그린 배양액을 넣을곳 !check[i] : 레드 배양액을 넣을 곳
		for (int i = 0; i < G + R; i++) {
			if (check[i]) {
				checkG[seed[i].h][seed[i].y] = 1;
				Gr.push(pos({ seed[i].h, seed[i].y }));
			}
			else {
				checkR[seed[i].h][seed[i].y] = 1;
				Re.push(pos({ seed[i].h, seed[i].y }));
			}
		}
		BFS();
		// 꽃이 만들어진 곳 세기
		made = 0;
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (checkMade[hang][yal]) made++;
			}
		}
		//갱신
		if (result < made) result = made;
		return;
	}
	for (int s = start; s < G + R; s++) {
		check[s] = true;
		DFS1(depth + 1, s + 1);
		check[s] = false;
	}
}
// 배양액을 넣을 수 있는 곳중에 R + G 개만큼 뽑아 낸다..(순열)
void DFS(int depth, int start) {
	if (depth == G + R) {
		DFS1(0, 0);
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		seed[depth] = { Vec[s].h, Vec[s].y };
		DFS(depth + 1, s + 1);
		seed[depth] = { 0, 0 };
	}
}