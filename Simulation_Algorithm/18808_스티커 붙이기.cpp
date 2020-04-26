/*
	https://www.acmicpc.net/problem/18808
	K���� ��ƼĿ�� �����鼭 0, 90, 180, 270�������� ���� �� �ִ��� ������ �Ǵ��ϴ� �˰��� ����.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;
int board[11][11];
int tmp_board[4][11][11]; // board�� ���� 0, 90, 180, 270���� ���� �ִ� �迭..
bool check[41][41]; // ��ƼĿ�� ���̴� check�迭..
bool flag;
bool checkFlag;
int result;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int a, b, s = 0; s < K; s++) {
		scanf("%d %d", &a, &b);
		for (int hang = 0; hang < a; hang++) {
			for (int yal = 0; yal < b; yal++) {
				scanf("%d", &board[hang][yal]);
				tmp_board[0][hang][yal] = board[hang][yal]; // board 0���� tmp_board�� �ִ´�.
			}
		}

		for (int i = 0; i < 4; i++) { // board�� 0, 90, 180, 270�� ���� ���� ��������.. 
			int tmpA = 0; int tmpB = 0; checkFlag = false;
			if (i == 0 || i == 2) { // 0, 180�� �� ���� board�� hang, yal �� ����..
				tmpA = a; tmpB = b;
			}
			if (i == 1 || i == 3) { // 90, 270�� �� ��� board�� hang, yal�� �ٲ�.
				tmpA = b; tmpB = a;
			}
			for (int hang = 0; hang < N; hang++) {
				if (hang + tmpA > N) break; // ��ƼĿ(tmp_board)�� ���� �� �ִ�(check)�迭�� �Ѿ�� break;
				for (int yal = 0; yal < M; yal++) {
					if (yal + tmpB > M) break; // ��ƼĿ(tmp_board)�� ���� �� �ִ�(check)�迭�� �Ѿ�� break;
					flag = false; // check�� hang, yal�� ���ư��� ��ƼĿ�� ���� �� �ִ��� �Ǵ�..					
						for (int r = 0; r < tmpA; r++) {
							for (int c = 0; c < tmpB; c++) {
								
								if (tmp_board[i][r][c] == 1) { // ��ƼĿ�� �ٿ��ߵǴ� ����
									if (check[r + hang][c + yal]) { // ��ƼĿ�� �̹� �پ�������
										flag = true; // flag= true�� ���� �����̴� ���� ����..
										break;
									}
								}
							}
							if (flag) break;
						}
						if (!flag) { // ��ƼĿ�� ���� �� �ִ� hang, yal�̸�
							for (int r = 0; r < tmpA; r++) {
								for (int c = 0; c < tmpB; c++) {
									if (tmp_board[i][r][c] == 1) { // tmp_board�� 1�� �� ��ƼĿ�� ���̴� check���� true�� ��ȯ..
										check[hang + r][yal + c] = true;
									}
								}
							}
							checkFlag = true;		// ��ƼĿ�� �ٿ��ٴ� ��ȣ.
						}
					
					if (checkFlag) break;
				}
				if (checkFlag) break;
			}
			if (i == 3) break; // 270������ �� ������break;

			if (checkFlag) break;		
			else { // board�� ȸ���ϴ� ��..
				for (int hang = 0; hang < tmpB; hang++) {
					for (int yal = 0; yal < tmpA; yal++) {
						tmp_board[i + 1][hang][yal] = tmp_board[i][tmpA -1 - yal][hang];
					}
				}
			}
		}
		memset(tmp_board, 0, sizeof(tmp_board)); // ���� ��ƼĿ�� ���� tmp_board�ʱ�ȭ..
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (check[hang][yal]) result++;
		}
	}

	printf("%d\n", result);
	return 0;
}