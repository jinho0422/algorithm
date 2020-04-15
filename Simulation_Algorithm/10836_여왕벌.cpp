/*
	https://www.acmicpc.net/problem/10836
	M�ʱ��� board[hang-1][0]���� board[1][0]���� board[0][0]���� board[0][yal -1] ����
	�������� numbers�迭�� �־� ������ �����ϰ� board[1][1] ���� board[N -1][N -1]����
	����, ����, ���������� max���� ã�� �����ϴ� �˰��� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N, M;
int board[701][701];
int numbers[1501]; //M�ʱ��� board[hang-1][0]���� board[1][0]���� board[0][0]���� board[0][yal -1] ���� �������� �ִ� �迭..
 
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < 2 * N - 1; i++) numbers[i] = 1; // 1�� �ʱ�ȭ..

	for (int a, b, c, i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &c); // 0++ 1++ 2++�� � �ִ��� ����
		int num = a; // 0++�� ������� ������ ��ġ�� �����Ƿ� num �ʱⰪ�� a�� ����
		for (int j = 0; j < b; j++) { // numbers�迭�� ����  b���� 1++�� �����ϰ�
			numbers[num++] += 1;
		}
		for (int j = 0; j < c; j++) {// numbers�迭�� ���� c���� 2++�� �����ϰ�
			numbers[num++] += 2;
		}
	}
	int cnt = 0; // board�迭�� ���� ���ʾƷ����� ���� ���������� ���� ���� ���ʺ��� ���� ���� �����ʱ��� numbers�迭�� ���� ����
	for (int hang = N - 1; hang > 0; hang--) {
		board[hang][0] = numbers[cnt++];
	}
	for (int yal = 0; yal < N; yal++) {
		board[0][yal] = numbers[cnt++];
	}

	// board[1][1]���� board[N -1][N -1] ������ ���� ���� �������� ���� �ִ밪�� board���� ����.
	for (int hang = 1; hang < N; hang++) {
		for (int yal = 1; yal < N; yal++) {
			int up_max = max(board[hang - 1][yal - 1], board[hang - 1][yal]);
			board[hang][yal] = max(up_max, board[hang][yal - 1]);
		}
	}
	//����� ���
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			printf("%d ", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}