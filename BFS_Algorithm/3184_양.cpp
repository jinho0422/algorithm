#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
char str[251];
char board[251][251];
bool check[251][251];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int vNum, oNum;
typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;

void BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'v') vNum++; // vNum : 총 늑대의 수
			else if (board[hang][yal] == 'o') oNum++; // oNum : 총 양의 수
		}
	}
	// 울타리가 처진 각 영역별로 늑대와 양 세기..
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (!check[hang][yal] && (board[hang][yal] == '.' || board[hang][yal] == 'v' || board[hang][yal] == 'o')) {
				BFS(hang, yal);
			}
		}
	}
	printf("%d %d\n", oNum, vNum);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	int vN = 0, oN = 0;
	if (board[hang][yal] == 'v') vN++;
	else if (board[hang][yal] == 'o') oN++;
	Q.push(pos({ hang, yal }));
	

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

			if (!check[newY][newX]) {
				check[newY][newX] = true;
				if (board[newY][newX] == 'v') vN++;
				else if (board[newY][newX] == 'o') oN++;
				Q.push(pos({ newY, newX }));
			}
		}
	}
	// 각 영역에서 늑대의 갯수가 더 많거나 같으면 양의 총양에서 영역안의 양을 빼고 반대이면 늑대의 총양에서 영역안의 늑대를 뺀다.
	if (vN >= oN) oNum -= oN;
	else vNum -= vN;
}