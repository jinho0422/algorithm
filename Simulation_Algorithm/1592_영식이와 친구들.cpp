#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


int N, M, L;
int board[1001];

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &L);
	//ù��° ����� �޴� ��
	board[1] = 1;
	//���� �������� �����ִ� ����
	int ball = 1;
	// �����
	int cnt = 0;
	while (1) {
		cnt++;
		// ¦���϶��� L��ŭ �����̰� ������ �ɾ� �����Ƿ� ball�� ���� 0�� �Ǹ� ����� ���� �����ش�.
		if (board[ball] / 2 == 0) {
			ball -= L;
			if (ball <= 0) ball += N;
			board[ball]++;
			if (board[ball] == M) break;
		}
		//Ȧ���϶��� L��ŭ �ð�������� �����̰� ����� ������ ball�� Ŀ���� ����� ����ŭ ���ش�.
		else {
			ball += L;
			if (ball > N) ball -= N;
			board[ball]++;
			if (board[ball] == M) break;
		}
	}
	printf("%d\n", cnt);
	return 0;
}