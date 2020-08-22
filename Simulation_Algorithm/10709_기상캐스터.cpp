#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[102];
char board[102][102];

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	// board�� ���鼭
	for (int hang = 0; hang < N; hang++) {
		bool findCloud  = false; // �� �ึ�� ������ �־��� ���� ������ true �ƴϸ� false
		int minute = 0;
		for (int yal = 0; yal < M; yal++) {
			// ������ �ƴҶ� ������ �ѹ��� ��Ÿ���� �ʾ����� -1, ������ ��Ÿ�������� ������ minute�� ���
			if (board[hang][yal] == '.') {
				if (!findCloud) printf("-1 ");
				else {
					printf("%d ", minute);
					minute++;
				}
			}	
			// ������ ������ findCloud == true, minute�� ���� �����Ѵ�.
			if (board[hang][yal] == 'c') {
				findCloud = true;
				minute = 0;
				printf("%d ", minute);
				minute++;
			}
		}
		printf("\n");
	}
	return 0;
}