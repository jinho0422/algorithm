/*
  사탕게임 문제는 N*N 크기에 사탕이 채워져 있는데 인접한 곳에 다른 색의 사탕이 있으면
  사탕을 바꾸고 행 또는 열에 같은색의 사탕이 있으면 먹을 수 있다.
  이 중 행과 열에 같은 색의 갯수가 최대일 때를 구하는 문제이다.
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
char tmp_board[51][51]; // 행과 열이 다를 때 board를복사하고 사탕을 바꿀 때 사용.
int dirY[2] = { 0, 1 }; // 행과 열을 전체적으로 다 볼 것이므로 각각의 행과 열에서 동, 남쪽만 보면 된다.
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
			for (int dir = 0; dir < 2; dir++) {  //각각의 행렬에서 인접한 사탕이 다른지를 보려고..
				int newY = hang + dirY[dir]; 
				int newX = yal + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (board[hang][yal] != board[newY][newX]) { // 인접한 곳에 사탕의 색이 다르면..
					memcpy(tmp_board, board, sizeof(tmp_board)); // board를 복사..

					char temp = tmp_board[hang][yal]; // 사탕을 바꾸기 위해서..
					tmp_board[hang][yal] = tmp_board[newY][newX];
					tmp_board[newY][newX] = temp;
					
				
					for (int hang1 = 0; hang1 < N; hang1++) {
						cnt = 1;
						for (int yal1 = 0; yal1 < N -1 ; yal1++) {
							if (tmp_board[hang1][yal1] == tmp_board[hang1][yal1 + 1]) { // 열에서 사탕이 같으면 cnt를 증가시키고
								cnt++;
								if (result < cnt) result = cnt; // 최대로 먹을 수 있는 갯수를 체크..
							}
							else { // 다르면 그 전의 갯수를 체크하고 cnt를 1로 만든다..
								if (result < cnt) result = cnt;
								cnt = 1;
							}
						}
					}

					for (int yal1 = 0; yal1 < N; yal1++) { // 위와 같은 방법으로 행을 본다..
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