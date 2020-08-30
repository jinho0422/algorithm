#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
char str[502];
char board[502][502];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '.') board[hang][yal] = 'D'; // 늑대가 움직일 수 있는 곳은 울타리를 친다..
			if (board[hang][yal] == 'W') { // 늑대이면 넣는다..
				Q.push(pos({ hang, yal }));
			}
		}
	}
	int sz = Q.size();
	for (int s = 0; s < sz; s++) { // 늑대의 위치에서 상하좌우를 보고 양이 있는지만 판단..
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
			 // 있을 때 출력..
			if (board[newY][newX] == 'S') {
				printf("0\n");
				return 0;
			}
		}
	}
	// 모두 없다면 출력..
	printf("1\n");
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			printf("%c", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
	// 사실 이 문제는 양을 보고 상하좌우를 보고 늑대가 있으면 0을 출력하고 없으면 '.'를 'D'로 울타리를 만들어서 최종으로 출력하면 시간이 더 절약될 것이다.
}
