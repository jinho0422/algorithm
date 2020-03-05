/*
  N*M 크기의 보드에서 '.'는 바다이고, '1'~'9'까지는 튼튼함의 정도이다.
  상, 하, 좌, 우, 대각선을 보고 바다의 갯수가 튼튼함의 갯수보다 많거나 같으면 모래성은 무너진다.
  모래성이 무너지지 않는 시간을 구하는 문제이다.

  처음에는 모래성을 Q에 넣어서 모래성이 무너지는지를 판단하고 무너지면 또다른 Q에 넣고
  아니면 기존 Q에 다시넣어 또다른 Q에 있는 곳을 '.'바다로 만들고 다시 돌리고 하였다.
  하지만 같은곳을 계속적으로 상, 하, 좌, 우, 대각선을 판단해야되서 시간초과가 발생했다.
  그래서 바다를 Q에 넣고 상, 하, 좌, 우, 대각선을 보면서 모래성이면 count하여 모래성이 부서지는 
  경우가 생기면 Vector에 넣어 바다로 만들어주고 그곳을 Q에 넣어 돌려주면서 상황을 해결했다.
  */


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
char str[1001];
char board[1001][1001];
int count_board[1001][1001]; // 모래성이 부서지는지를 conut하기 위한 보드..
bool check[1001][1001]; // 모래성이 부서진 곳인지를 판단하는 check
int dirY[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int result;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // 부서질 수 있는 모래성을 넣는 Vector
queue<pos> Q; // 바다를 넣는 Q..

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '.') Q.push(pos({ hang, yal })); // 바다인 곳은 Q에 넣는다.
		}
	}


	while (1) {

		bool result_flag = false; // 더이상 모래성이 부서지지 않는지 부서질 수 있는지를 판단..

		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();


			for (int dir = 0; dir < 8; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] != '.' && !check[newY][newX]) { // 부서지지 않은 모래성이면..
					count_board[newY][newX] += 1; // 바다에 인접하고 있으므로 모래성의 count를 증가..
					if (count_board[newY][newX] >= board[newY][newX] - '0') {// 모래성의 튼튼함보다 인접한 바다가 크거나 같으면
						check[newY][newX] = true; // 모래성이 부서질 수 있다 판단하고
						Vec.push_back(pos({ newY, newX })); // Vector에 넣는다.
						result_flag = true;// 결과값이 증가할 수 있다는 판단..
					}
				}
			}
		}

		int Vsz = Vec.size();
		for (int s = 0; s < Vsz; s++) {
			pos p = Vec[s];
			Q.push(pos({ p.h, p.y })); // 바다를 Q에 넣는 과정..
			board[p.h][p.y] = '.'; // 부서진 모래성을 바다로 만드는 과정..
		}
		Vec.clear();// Q에넣은바다를 클리어..

		if (result_flag) result++;
		else break;
	}

	printf("%d\n", result);
	return 0;
}