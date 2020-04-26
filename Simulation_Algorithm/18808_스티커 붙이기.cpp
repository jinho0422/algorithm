/*
	https://www.acmicpc.net/problem/18808
	K개의 스티커를 받으면서 0, 90, 180, 270돌려가며 붙일 수 있는지 없는지 판단하는 알고리즘 구현.
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
int tmp_board[4][11][11]; // board의 값을 0, 90, 180, 270돌린 값을 넣는 배열..
bool check[41][41]; // 스티커를 붙이는 check배열..
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
				tmp_board[0][hang][yal] = board[hang][yal]; // board 0도를 tmp_board에 넣는다.
			}
		}

		for (int i = 0; i < 4; i++) { // board를 0, 90, 180, 270도 돌린 값을 보기위해.. 
			int tmpA = 0; int tmpB = 0; checkFlag = false;
			if (i == 0 || i == 2) { // 0, 180도 일 때는 board의 hang, yal 이 유지..
				tmpA = a; tmpB = b;
			}
			if (i == 1 || i == 3) { // 90, 270도 일 대는 board의 hang, yal이 바뀜.
				tmpA = b; tmpB = a;
			}
			for (int hang = 0; hang < N; hang++) {
				if (hang + tmpA > N) break; // 스티커(tmp_board)가 붙일 수 있는(check)배열을 넘어가면 break;
				for (int yal = 0; yal < M; yal++) {
					if (yal + tmpB > M) break; // 스티커(tmp_board)가 붙일 수 있는(check)배열을 넘어가면 break;
					flag = false; // check의 hang, yal을 돌아가며 스티커를 붙일 수 있는지 판단..					
						for (int r = 0; r < tmpA; r++) {
							for (int c = 0; c < tmpB; c++) {
								
								if (tmp_board[i][r][c] == 1) { // 스티커를 붙여야되는 곳에
									if (check[r + hang][c + yal]) { // 스티커가 이미 붙어있으면
										flag = true; // flag= true를 통해 못붙이는 곳을 인지..
										break;
									}
								}
							}
							if (flag) break;
						}
						if (!flag) { // 스티커를 붙일 수 있는 hang, yal이면
							for (int r = 0; r < tmpA; r++) {
								for (int c = 0; c < tmpB; c++) {
									if (tmp_board[i][r][c] == 1) { // tmp_board가 1일 때 스티커를 붙이는 check값을 true로 변환..
										check[hang + r][yal + c] = true;
									}
								}
							}
							checkFlag = true;		// 스티커를 붙였다는 신호.
						}
					
					if (checkFlag) break;
				}
				if (checkFlag) break;
			}
			if (i == 3) break; // 270도까지 다 봤으면break;

			if (checkFlag) break;		
			else { // board를 회전하는 곳..
				for (int hang = 0; hang < tmpB; hang++) {
					for (int yal = 0; yal < tmpA; yal++) {
						tmp_board[i + 1][hang][yal] = tmp_board[i][tmpA -1 - yal][hang];
					}
				}
			}
		}
		memset(tmp_board, 0, sizeof(tmp_board)); // 다음 스티커를 위해 tmp_board초기화..
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (check[hang][yal]) result++;
		}
	}

	printf("%d\n", result);
	return 0;
}