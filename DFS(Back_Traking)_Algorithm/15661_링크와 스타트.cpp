/*
	https://www.acmicpc.net/problem/15661
	두팀으로 나눌 때 한팀에 적어도 한명이상의 플레이어가 있어야된다.
	조합을 이용하여 한팀의 player를 설정하여 능력치를 구하는 알고리즘 구현.. 
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int board[21][21];
int player[21]; // 1팀 player
int player1[21]; // 2팀 player
bool check[21]; // 2팀 player를 설정하기 위해..
int sum1; // 1팀 능력치
int sum2; // 2팀 능력치
int result;

void solve(int depth, int start);

int main() {
	result = 2147000000;
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	solve(0, 0);
	printf("%d\n", result);
	return 0;
}

void solve(int depth, int start) { // 조합을 활용한 팀 plyer 설정..
	if (depth != 0 && depth != N) { // 한팀에 player한명 이상이 있기 위한 설정..
		sum1 = 0; sum2 = 0;
		for (int i = 0; i < depth; i++) { // 1팀의 능력치 구하기.
			for (int j = i + 1; j < depth; j++) {
				sum1 += board[player[i]][player[j]] + board[player[j]][player[i]];
			}
		}
		int num = 0;
		for (int i = 0; i < N; i++) { // 2팀의 player 설정
			if (!check[i]) player1[num++] = i;
		}
		for (int i = 0; i < num; i++) { // 2팀 능력치 구하기..
			for (int j = i + 1; j < num; j++) {
				sum2 += board[player1[i]][player1[j]] + board[player1[j]][player1[i]];
			}
		}
		if (result > abs(sum1 - sum2)) result = abs(sum1 - sum2); // 결과값갱신..
	}
	if (depth == N) return; // 전체 player 수가 넘어가면 return.. 

	for (int i = start; i < N; i++) { // 조합을 이용한 player구하기..
		player[depth] = i;
		check[i] = true; // true는 1팀 player false는 2팀 player..
		solve(depth + 1, i + 1);
		player[depth] = 0;
		check[i] = false;
	}
}