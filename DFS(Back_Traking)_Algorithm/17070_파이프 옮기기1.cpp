/*
	N * N�����ǿ��� �������� ��ġ�ϴµ� ó�� ��ġ�� ���η� ��ġ�Ǿ��ִ�.
	�����ǿ� ��ġ�� �� �ִ� �������� ����, ����, �밢���̰� �������� 0�� ��ġ�� �� �ִ°�, 1�� ������ ��ġ�� �� ���°��̴�.
	���η� ��ġ�ϰ� ������ ����, �밢�� �������� ��ġ�� ���ְ� ���δ� ����, �밢��, �밢���� ��� �������� ��ġ�� �� �ִ�.
	�������� �� N, �� N���� �����ϴ� ���� ��� ������ �̾Ƴ��� �����̴�.

	���Ʈ������ Ȱ���Ͽ� �������� ��ġ�� �� �ִ� ��� ���� ���캸�鼭 ��� ���� N���� ������ �� �ִ��� ã�Ҵ�.
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
int dirY[3] = { 0, 1, 1 }; // ���� == 0 ���� == 1 �밢�� == 2
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

	solve(1, 2, 0); // ó�� ��ġ�� ���η� �̸� ��ġ�Ǿ� �־ �� 1, �� 2, ���μ�ġ 0�� �־���.
	printf("%d\n", result);

	return 0;
}

bool find_dir(int a, int b) { // ��ġ�� �������� ���� ��ġ�� �� �ִ� �������� ã�� �Լ�..
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

bool go_flag(int hang, int yal) { // �밢�� �������� ��ġ�� �� �ִ��� �Ǵ��ϴ� �Լ� ..
	for (int dir = 0; dir < 3; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY <= 0 || newY > N || newX <= 0 || newX > N || check[newY][newX] || board[newY][newX] == 1) return false;
	}
	return true;
}

void solve(int hang, int yal, int d) {
	if (hang == N && yal == N) {
		result++; // ��, ���� N�� �������� �� �����++
		return;
	}

	for (int dir = 0; dir < 3; dir++) {
		bool flag = find_dir(d, dir); // ��ġ�� �������� ���� ��ġ�� �� �ִ� ����� ������ ã��..
		if (!flag) continue;
		else {
			if (dir == 0 || dir == 1) { // ����, ���� ��������ġ..
				int newY = hang + dirY[dir];
				int newX = yal + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N || check[newY][newX] || board[newY][newX] == 1) continue;
				if (!check[newY][newX]) {
					check[newY][newX] = true;
					solve(newY, newX, dir);
					check[newY][newX] = false;

				}
			}
			else if (dir == 2) { // �밢�� ������ ��ġ.. 

				bool flag1 = go_flag(hang, yal); // �밢�� �������� ��ġ�� �� �ִ��� �Ǵ�..

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


