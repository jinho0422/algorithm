#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;

int N;
char tmp[40]; // ���� ������ ���Ҹ� �ֱ� ����..
char board[6][6];
int dirY[2] = { 0, 1 }; // 0 : ������, 1 : �Ʒ���
int dirX[2] = { 1, 0 };
int minResult, maxResult; // �����


void DFS(int depth, int hang, int yal);

int main() {
	minResult = 2147000000;
	maxResult = -2140000000;
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			cin >> board[hang][yal];
		}
	}
	tmp[0] = board[0][0];
	DFS(1, 0, 0);
	printf("%d %d\n", maxResult, minResult);
	return 0;
}

void DFS(int depth, int hang, int yal) {
	if (hang == N - 1 && yal == N - 1) { //���� ������ �������� �����ϸ�
		int sum = tmp[0] -'0'; // ó������ sum�� �ְ�
		// tmp�� ����ִ� ���鿡�� ��ȣ�� ���� �� �������� ��ȣ�� ���� sum�� ����..(i+= 2)�� ��ȣ�� ��������..
		for (int i = 1; i < depth ; i += 2) {
			if (tmp[i] == '+') sum += (tmp[i + 1] - '0');
			else if (tmp[i] == '-') sum -= (tmp[i + 1] - '0');
			else if (tmp[i] == '*') sum *= (tmp[i + 1] - '0');
		}
		// ����� ����..
		if (minResult > sum) minResult = sum;
		if (maxResult < sum) maxResult = sum;
		return;
	}
	for (int dir = 0; dir < 2; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];
		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
		tmp[depth] = board[newY][newX];
		DFS(depth + 1, newY, newX);
	}
}