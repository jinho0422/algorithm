/*
	https://www.acmicpc.net/problem/17025
	���� ū ���̽�ũ���� ũ��� ũ�Ⱑ ���� ū ���̽�ũ���߿� �ѷ��� ���� ���� ���̽�ũ����
	�ѷ��� ���ϴ� ������ BFS�� �̿��Ͽ� �˰��� ����.
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

typedef struct _pos { // hang yal�� ���� �� �ִ� struct.
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

	for (int hang = 1; hang <= N; hang++) { // board�� ���鼭 ���̽�ũ���� ���̸� BFS�� ���� size check..
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

			if (board[newY][newX] != '#') icePerimeter++; // ���̽�ũ���� �ѷ��� check..

			if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

			if (board[newY][newX] == '#' && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos{ newY, newX });
				iceSize++;
			}
		}
	}
	// ������ ���̽�ũ���� ũ�Ⱑ ������ check�Ǿ��� ���̽�ũ��ũ�⺸�� ũ��..
	if (Icesizeresult < iceSize) {
		Icesizeresult = iceSize; // ����� ������ ���ְ�
		PerimeterResult = icePerimeter; // ���̽�ũ�� �ѷ��� ������� ����..
	}
	if (Icesizeresult == iceSize) { // ���� ���̽�ũ���� ũ�Ⱑ ������ ���̽�ũ���� �ѷ��� ���� �� ����..
		if (PerimeterResult > icePerimeter) PerimeterResult = icePerimeter;
	}
}