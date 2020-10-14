#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int board[10][10];
int paper[6];
int oneNum;
int result;

void DFS(int hang, int yal, int cnt);

int main() {
	//�Է�
	result = 987654321;
	for (int i = 1; i <= 5; i++) paper[i] = 5;
	for (int hang = 0; hang < 10; hang++) {
		for (int yal = 0; yal < 10; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) oneNum++; // ���־ߵ� ����
		}
	}
	//���־ߵɰ��� ������ 0���
	if (oneNum == 0) {
		printf("0\n");
		return 0;
	}
	DFS(0, 0, oneNum);
	//���
	if (result != 987654321) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}
// ���� �� �ִ��� ����.. false : ���� �� ����, true : ���� �� ����
bool solve(int hang, int yal, int s) {
	if (hang + s > 10 || yal + s > 10) return false; // ��谪�� �Ѿ�� ��..
	if (paper[s] == 0) return false; // ���̰� ������
	for (int i = hang; i < hang + s; i++) {
		for (int j = yal; j < yal + s; j++) {
			if (board[i][j] == 0) return false; // ���簢���� �ƴϸ�..
		}
	}
	return true;
}

void DFS(int hang, int yal, int cnt) {
	if (yal >= 10) {
		hang += 1, yal = 0; // ��谪�� ������ hang + 1, yal = 0
	}
	// ���־ߵɰ��� ��� ��������
	if (cnt == 0) {
		int sum = 25;
		for (int i = 1; i <= 5; i++) sum -= paper[i]; //����� ���� ����..
		if (result > sum) result = sum; // ����� ����..
		return;
	}
	if (hang >= 10) return; // 10, 10���� ���� ����..
	//ä���� �� ���� ��Ÿ����
	if (board[hang][yal] == 1) {
		for (int s = 5; s >= 1; s--) {
			bool flag = solve(hang, yal, s);
			if (flag) {
				paper[s]--;
				for (int i = hang; i < hang + s; i++) {
					for (int j = yal; j < yal + s; j++) {
						cnt--;
						board[i][j] = 0;
					}
				}
				DFS(hang, yal + s, cnt);
				paper[s]++;
				for (int i = hang; i < hang + s; i++) {
					for (int j = yal; j < yal + s; j++) {
						cnt++;
						board[i][j] = 1;
					}
				}
			}
		}
	}
	else DFS(hang, yal + 1, cnt); // ä���ߵ� ���� ������ yal + 1
}
