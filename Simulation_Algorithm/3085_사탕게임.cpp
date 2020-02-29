/*
  �������� ������ N*N ũ�⿡ ������ ä���� �ִµ� ������ ���� �ٸ� ���� ������ ������
  ������ �ٲٰ� �� �Ǵ� ���� �������� ������ ������ ���� �� �ִ�.
  �� �� ��� ���� ���� ���� ������ �ִ��� ���� ���ϴ� �����̴�.
  */


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N;
char  str[51];
char board[51][51];
char tmp_board[51][51]; // ��� ���� �ٸ� �� board�������ϰ� ������ �ٲ� �� ���.
int dirY[2] = { 0, 1 }; // ��� ���� ��ü������ �� �� ���̹Ƿ� ������ ��� ������ ��, ���ʸ� ���� �ȴ�.
int dirX[2] = { 1, 0 };
int result;
int cnt;


int main() {
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal];
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			for (int dir = 0; dir < 2; dir++) {  //������ ��Ŀ��� ������ ������ �ٸ����� ������..
				int newY = hang + dirY[dir]; 
				int newX = yal + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (board[hang][yal] != board[newY][newX]) { // ������ ���� ������ ���� �ٸ���..
					memcpy(tmp_board, board, sizeof(tmp_board)); // board�� ����..

					char temp = tmp_board[hang][yal]; // ������ �ٲٱ� ���ؼ�..
					tmp_board[hang][yal] = tmp_board[newY][newX];
					tmp_board[newY][newX] = temp;
					
				
					for (int hang1 = 0; hang1 < N; hang1++) {
						cnt = 1;
						for (int yal1 = 0; yal1 < N -1 ; yal1++) {
							if (tmp_board[hang1][yal1] == tmp_board[hang1][yal1 + 1]) { // ������ ������ ������ cnt�� ������Ű��
								cnt++;
								if (result < cnt) result = cnt; // �ִ�� ���� �� �ִ� ������ üũ..
							}
							else { // �ٸ��� �� ���� ������ üũ�ϰ� cnt�� 1�� �����..
								if (result < cnt) result = cnt;
								cnt = 1;
							}
						}
					}

					for (int yal1 = 0; yal1 < N; yal1++) { // ���� ���� ������� ���� ����..
						cnt = 1;
						for (int hang1 = 0; hang1 < N -1; hang1++) {
							if (tmp_board[hang1][yal1] == tmp_board[hang1 + 1][yal1]) {
								cnt++;
								if (result < cnt) result = cnt;
							}
							else {
								if (result < cnt) result = cnt;
								cnt = 1;
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n", result);

	return 0;
}