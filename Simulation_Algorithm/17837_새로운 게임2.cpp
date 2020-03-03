/*
 N*N 체스판에서 말의 개수가 K개를 사용하여 4개이상의 말이 쌓이면 결과값을 출력한다.
 체스판의 각 칸은 흰색, 빨간색, 파란색으로 되어있고  1 ~ K말은 순서대로 움직이면 한번의 결과값이 증가한다.
 말이 있는 자리에서 움질일려는 체스판의 색이 흰색이면 시작말부터 그 위에 말은 그대로 움직일려는 체스판으로 이동하고
 빨간색이면 순서를 바꿔서 이동, 파란색이면 방향을 바꿔서 이동한다..
 */


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int board[15][15];
int dirY[5] = { 0, 0, 0, -1, 1 };
int dirX[5] = { 0, 1, -1, 0, 0 };


deque<int> Q[15][15]; // 각 체스판에 어떠한 말이 있는지 확인하기 위한 Q..
int tmp[15]; // 말이 움직일 때 빨간색 체스판이면 순서를 바꿔서 움직이기 위해..

typedef struct _pos1 { // 말의 행과 열 움직이는 방향을 넣어주는 struct
	int h, y, d;
}pos1;
pos1 holes[13]; 



int change_D(int d) { // 파란색 or 체스판을 벗어나면 방향을 바꿔주기 위한 함수..
	if (d == 1) return 2;
	else if (d == 2) return 1;
	else if (d == 3) return 4;
	else if (d == 4) return 3;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int a, b, c, i = 1; i <= K; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a][b].push_front(i); // 말의 번호를 넣어주기..
		holes[i] = { a, b, c }; // 말의 정보를 넣어주기..
	}
	int result = 0;

	while (1) {
		result++;
		if (result > 1000) { // 결과값이 1000을 넘으면 실패를 뜻함.
			printf("-1\n");
			return 0;
		}
		for (int i = 1; i <= K; i++) {
			int ih = holes[i].h; // 각각의 말의 정보를 ih, iy, id에 저장..
			int iy = holes[i].y;
			int id = holes[i].d;

			int sz = Q[ih][iy].size(); // i번째 말이 있는 큐에서의 사이즈를 체크..
			bool flag = false;

			for (int s = 0; s < sz; s++) {
				if (flag) break; // i번째 말을 찾고 움직임 후 다음번 말로 가기위해..
				int p = Q[ih][iy].front();

				if (i != p) { // Q에 있는 말이 원하는 말이 아닐 때는 Q의 뒤로 옮겨준다.
					Q[ih][iy].pop_front();
					Q[ih][iy].push_back(p);
				}

				else if (i == p) { // i 번째 말이 나타나면 
					flag = true;
					int newY = ih + dirY[id];
					int newX = iy + dirX[id];

					if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 2) {
						// 움직일려는 체스판이 파란색이거나 체스판 범위를 벗어나면..
						int newD = change_D(id); // 말의 방향을 바꿔주고

						int nnewY = ih + dirY[newD];
						int nnewX = iy + dirX[newD];
						holes[i].d = newD; // 말의 방향정보를 다시저장..

						if (nnewY <= 0 || nnewY > N || nnewX <= 0 || nnewX > N || board[nnewY][nnewX] == 2) {
							//방향을 바꿧을 때 다시 파란색과 체스판을 벗어나면..
							for (int s1 = 0; s1 < sz - s; s1++) { // 원상복귀..
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();
								Q[ih][iy].push_back(p1);
							}
						}
						else if (board[nnewY][nnewX] == 1) { // 움직일려는 체스판이 빨간색이면
							int num = 0;
							for (int s1 = 0; s1 < sz - s; s1++) { // i번째말부터 그위에 말을 tmp에 저장하고
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();

								tmp[num++] = p1;
							}
							for (int s1 = num - 1; s1 >= 0; s1--) { // 움직일려는 체스판으로 반대로 넣어준다.
								holes[tmp[s1]].h = nnewY; // 말의 정보를 바꿔준다.
								holes[tmp[s1]].y = nnewX;
								Q[nnewY][nnewX].push_back(tmp[s1]);
							}
							if (Q[nnewY][nnewX].size() >= 4) { // 움직이고 나서 움직인 곳의 말이 4개이상인지 확인..
								printf("%d\n", result);
								return 0;
							}
						}
						else if (board[nnewY][nnewX] == 0) { // 움직일려는 체스판이 흰색이면 현재의 말부터 위에 있는 말까지 다음 체스판으로 이동..
							for (int s1 = 0; s1 < sz - s; s1++) {
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();

								holes[p1].h = nnewY; // 말의 정보를 바꿔준다.
								holes[p1].y = nnewX;
								Q[nnewY][nnewX].push_back(p1);
							}
							if (Q[nnewY][nnewX].size() >= 4) {// 움직이고 나서 움직인 곳의 말이 4개이상인지 확인..
								printf("%d\n", result);
								return 0;
							}
						}
					}

					else if (board[newY][newX] == 1) { // 움직일려는 체스판이 빨간색일때..
						int num1 = 0;
						for (int s1 = 0; s1 < sz - s; s1++) {
							int p1 = Q[ih][iy].front();
							Q[ih][iy].pop_front();
							tmp[num1++] = p1;
						}

						for (int s1 = num1 - 1; s1 >= 0; s1--) {
							holes[tmp[s1]].h = newY;
							holes[tmp[s1]].y = newX;
							Q[newY][newX].push_back(tmp[s1]);
						}
						if (Q[newY][newX].size() >= 4) {
							printf("%d\n", result);
							return 0;
						}
					}

					else if (board[newY][newX] == 0) { // 움직일려는 체스판이 흰색일 때..
						for (int s1 = 0; s1 < sz - s; s1++) {
							int p1 = Q[ih][iy].front();
							Q[ih][iy].pop_front();

							holes[p1].h = newY;
							holes[p1].y = newX;
							Q[newY][newX].push_back(p1);
						}

						if (Q[newY][newX].size() >= 4) {
							printf("%d\n", result);
							return 0;
						}
					}
				}
			}
		}
	}
}
