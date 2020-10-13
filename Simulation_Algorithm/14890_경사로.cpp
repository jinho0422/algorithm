#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

int N, L;
int board[101][101];
bool check[2][101]; //check[0][0~100] --> hang�� ���η� �Ϻ����� check[1][0~100] --> yal�� ���ΰ� �Ϻ�����
int result;

queue<int> Q;

void solve(int depth, int start);

int main() {
	//�Է�
	scanf("%d %d", &N, &L);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	//���� ���� ã��
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			Q.push(board[hang][yal]);
		}
		solve(0, hang);
		while (!Q.empty()) Q.pop();
		//���ʿ��� ���� ���ΰ� �ȵɽ�..
		if (!check[0][hang]) {
			for (int yal = N - 1; yal >= 0; yal--) {
				Q.push(board[hang][yal]);
			}
			solve(0, hang);
			while (!Q.empty()) Q.pop();
		}
	}
	//���� ���� ã��
	for (int yal = 0; yal < N; yal++) {
		for (int hang = 0; hang < N; hang++) {
			Q.push(board[hang][yal]);
		}
		solve(1, yal);
		while (!Q.empty()) Q.pop();
		// ������ ���� ���ΰ� �ȵɽ�..
		if (!check[1][yal]) {
			for (int hang = N - 1; hang >= 0; hang--) {
				Q.push(board[hang][yal]);
			}
			solve(1, yal);
			while (!Q.empty()) Q.pop();
		}
	}
	//����� ���� & ���
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j]) result++;
		}
	}
	printf("%d\n", result);
	return 0;
}

void solve(int depth, int start) {
	int first = Q.front();
	int checkFirst = Q.front(); // �ְ��� ã��
	int cnt = 0; // L��ŭ �ִ��� �Ǵ��ϱ� ����..
	bool flag = false; // ������ �ܰ谡 ���������� ���������� �Ǵ�.
	while (!Q.empty()) {
		int p = Q.front();
		if (checkFirst < p) checkFirst = p; // �ְ��� ����
		if (first == p) { // �����̶� ���̰� ������ cnt++
			Q.pop();
			cnt++;
		}
		// ���̰� �ٸ���
		else if (first != p) {
			if (first > p) { // ������ ���̰� �� Ŭ ��
				flag = true;
				if (checkFirst == first) cnt = L; // �ְ����̸� cnt == L�θ�����ش�
			}

			else if (first < p) { // ������ ���̰� �� Ŭ ��
				if (flag) { // ���� ������ �����Դ� ���� ������
					if (cnt < 2 * L) return; // �ٽ� �ö� �� �ִ��� �Ǵ�
					else flag = false;

				}
			}
			// cnt�� ������ ���̺��� Ŭ��..
			if (cnt >= L) {
				if (abs(first - p) == 1) {
					first = p;
					cnt = 0;
				}
				else return;
			}
			else return;
		}
	}
	// Ȱ�ַη� ����� �� �ִ��� ����..
	if (cnt >= L) check[depth][start] = true;
}