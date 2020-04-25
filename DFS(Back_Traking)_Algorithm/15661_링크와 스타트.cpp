/*
	https://www.acmicpc.net/problem/15661
	�������� ���� �� ������ ��� �Ѹ��̻��� �÷��̾ �־�ߵȴ�.
	������ �̿��Ͽ� ������ player�� �����Ͽ� �ɷ�ġ�� ���ϴ� �˰��� ����.. 
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int board[21][21];
int player[21]; // 1�� player
int player1[21]; // 2�� player
bool check[21]; // 2�� player�� �����ϱ� ����..
int sum1; // 1�� �ɷ�ġ
int sum2; // 2�� �ɷ�ġ
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

void solve(int depth, int start) { // ������ Ȱ���� �� plyer ����..
	if (depth != 0 && depth != N) { // ������ player�Ѹ� �̻��� �ֱ� ���� ����..
		sum1 = 0; sum2 = 0;
		for (int i = 0; i < depth; i++) { // 1���� �ɷ�ġ ���ϱ�.
			for (int j = i + 1; j < depth; j++) {
				sum1 += board[player[i]][player[j]] + board[player[j]][player[i]];
			}
		}
		int num = 0;
		for (int i = 0; i < N; i++) { // 2���� player ����
			if (!check[i]) player1[num++] = i;
		}
		for (int i = 0; i < num; i++) { // 2�� �ɷ�ġ ���ϱ�..
			for (int j = i + 1; j < num; j++) {
				sum2 += board[player1[i]][player1[j]] + board[player1[j]][player1[i]];
			}
		}
		if (result > abs(sum1 - sum2)) result = abs(sum1 - sum2); // ���������..
	}
	if (depth == N) return; // ��ü player ���� �Ѿ�� return.. 

	for (int i = start; i < N; i++) { // ������ �̿��� player���ϱ�..
		player[depth] = i;
		check[i] = true; // true�� 1�� player false�� 2�� player..
		solve(depth + 1, i + 1);
		player[depth] = 0;
		check[i] = false;
	}
}