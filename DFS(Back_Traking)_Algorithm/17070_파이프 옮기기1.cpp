/*
	N * N격자판에서 파이프를 설치하는데 처음 설치는 가로로 설치되어있다.
	격자판에 설치할 수 있는 파이프는 가로, 세로, 대각선이고 격자판의 0은 설치할 수 있는곳, 1은 벽으로 설치할 수 없는곳이다.
	가로로 설치하고 나서는 가로, 대각선 파이프만 설치할 수있고 세로는 세로, 대각선, 대각선은 모든 파이프를 설치할 수 있다.
	파이프가 행 N, 열 N으로 도달하는 경우는 몇가지 인지를 뽑아내는 문제이다.

	브루트포스를 활용하여 파이프가 설치될 수 있는 모든 곳을 살펴보면서 행과 열이 N으로 도달할 수 있는지 찾았다.
	*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int board[17][17];
int check[17][17];
int dirY[3] = { 0, 1, 1 }; // 가로 == 0 세로 == 1 대각선 == 2
int dirX[3] = { 1, 0, 1 };
int result;

void solve(int hang, int yal, int d);

int main() {
	scanf("%d", &N);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	solve(1, 2, 0); // 처음 설치시 가로로 미리 설치되어 있어서 행 1, 열 2, 가로설치 0을 넣었다.
	printf("%d\n", result);

	return 0;
}

bool find_dir(int a, int b) { // 설치된 파이프에 대한 설치할 수 있는 파이프를 찾는 함수..
	if (a == 0) {
		if (b == 0 || b == 2) return true;
		else return false;
	}
	if (a == 1) {
		if (b == 1 || b == 2) return true;
		else return false;
	}
	if (a == 2) {
		return true;
	}
}

bool go_flag(int hang, int yal) { // 대각선 파이프를 설치할 수 있는지 판단하는 함수 ..
	for (int dir = 0; dir < 3; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY <= 0 || newY > N || newX <= 0 || newX > N || check[newY][newX] || board[newY][newX] == 1) return false;
	}
	return true;
}

void solve(int hang, int yal, int d) {
	if (hang == N && yal == N) {
		result++; // 행, 열이 N에 도달했을 때 결과값++
		return;
	}

	for (int dir = 0; dir < 3; dir++) {
		bool flag = find_dir(d, dir); // 설치된 파이프에 대한 설치할 수 있는 모양의 파이프 찾기..
		if (!flag) continue;
		else {
			if (dir == 0 || dir == 1) { // 가로, 세로 파이프설치..
				int newY = hang + dirY[dir];
				int newX = yal + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N || check[newY][newX] || board[newY][newX] == 1) continue;
				if (!check[newY][newX]) {
					check[newY][newX] = true;
					solve(newY, newX, dir);
					check[newY][newX] = false;

				}
			}
			else if (dir == 2) { // 대각선 파이프 설치.. 

				bool flag1 = go_flag(hang, yal); // 대각선 파이프가 설치될 수 있는지 판단..

				if (flag1) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];
					check[newY][newX] = true;
					solve(newY, newX, dir);
					check[newY][newX] = false;
				}
			}
		}
	}
}


