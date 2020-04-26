/*
	https://www.acmicpc.net/problem/17025
	가장 큰 아이스크림의 크기와 크기가 가장 큰 아이스크림중에 둘레가 가장 작은 아이스크림의
	둘래를 구하는 문제로 BFS를 이용하여 알고리즘 구현.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

int N;
char str[1005];
char board[1005][1005];
bool check[1005][1005];  
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int iceSize;
int icePerimeter;

int Icesizeresult;
int PerimeterResult;

typedef struct _pos { // hang yal를 넣을 수 있는 struct.
	int h, y;
}pos;
queue<pos> Q;

void BFS(int hang, int yal);

int main() {
	PerimeterResult = 2147000000;
	scanf("%d", &N);
	for (int hang = 1; hang <= N; hang++) {
		scanf("%s", str);
		for (int yal = 1; yal <= N; yal++) {
			board[hang][yal] = str[yal - 1];
		}
	}

	for (int hang = 1; hang <= N; hang++) { // board를 돌면서 아이스크림인 곳이면 BFS를 통해 size check..
		for (int yal = 1; yal <= N; yal++) {
			if (board[hang][yal] == '#' && !check[hang][yal]) {
				BFS(hang, yal);
			}
		}
	}

	printf("%d %d\n", Icesizeresult, PerimeterResult);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	iceSize = 1;
	icePerimeter = 0;
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (board[newY][newX] != '#') icePerimeter++; // 아이스크림의 둘래를 check..

			if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

			if (board[newY][newX] == '#' && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos{ newY, newX });
				iceSize++;
			}
		}
	}
	// 현재의 아이스크림의 크기가 기존의 check되었던 아이스크림크기보다 크면..
	if (Icesizeresult < iceSize) {
		Icesizeresult = iceSize; // 결과값 갱신을 해주고
		PerimeterResult = icePerimeter; // 아이스크림 둘래의 결과값도 갱신..
	}
	if (Icesizeresult == iceSize) { // 만약 아이스크림의 크기가 같으면 아이스크림의 둘래가 작을 때 갱신..
		if (PerimeterResult > icePerimeter) PerimeterResult = icePerimeter;
	}
}