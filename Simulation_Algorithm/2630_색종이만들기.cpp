#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
using namespace std;

int N;
int board[135][135];
bool check[135][135];
int checkCnt[2];
int result[2];

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// checkPoint == ���� ���̸� ������ ����������.. breakCnt == �����̷� ä�õ� �κ��� ������ ���� while���� ��������������
	int checkPoint = N, breakCnt = N * N;
	// startH == while�� for�� ���� start ����, startY == ���� start ����
	int startH = 0, startY = 0;
	while (1) {
		for (int i = startH; i < startH + checkPoint; i++) {
			for (int j = startY; j < startY + checkPoint; j++) {
				if (check[i][j]) continue;
				if (board[i][j] == 0) checkCnt[0]++;
				else checkCnt[1]++;
			}
		}
		//���� for���� ���� checkCnt�� ���� �� ���� ������ ���̶� ������ �����̷� ����..
		if (checkCnt[0] == checkPoint * checkPoint) {
			result[0]++;
			for (int i = startH; i < startH + checkPoint; i++) {
				for (int j = startY; j < startY + checkPoint; j++) {
					check[i][j] = true;
				}
			}
			breakCnt -= checkPoint * checkPoint;
		}
		if (checkCnt[1] == checkPoint * checkPoint) {
			result[1]++;
			for (int i = startH; i < startH + checkPoint; i++) {
				for (int j = startY; j < startY + checkPoint; j++) {
					check[i][j] = true;
				}
			}
			breakCnt -= checkPoint * checkPoint;
		}
		// ������������ �Ǵ��ϴ� checkCnt �ʱ�ȭ..
		memset(checkCnt, 0, sizeof(checkCnt));

		// ���簢���� ��� �������� ���� ������ ������ �ٽõ���..
		if (startH + checkPoint == N && startY + checkPoint == N) {
			checkPoint /= 2;
			startH = 0, startY = 0;
		}
		// ���� ���簢���� �� ���� �ʾ����� ���� N(ó�� ���簢���� ����)�� ������ ���� checkPoint�� �����ְ� �����Ѵ�.
		else {
			if (startY + checkPoint == N) {
				startH += checkPoint;
				startY = 0;
			}
			else startY += checkPoint;
		}
		// ���� ���̸� �����γ����鼭 �� ���Ұų� ��� ���� �����̷� �����ִ� ���̸� break..
		if (checkPoint == 0 || breakCnt == 0) break;
	}
	//���
	for (int i = 0; i < 2; i++) printf("%d\n", result[i]);
	return 0;
}