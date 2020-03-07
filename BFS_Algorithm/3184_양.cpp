/*
	N*M마당에 '.'는 빈 마당, '#'는 울타리, 'o' 는 양, 'v'는 늑대이다.
	울타리쌓여있는 곳에서 밤에 양과 늑대의 수를 고려해서 늑대의 수가 많거나 같으면 양은 다 없어지고
	양의 수가 더 많으면 늑대가 다 없어진다..
	아침이 되었을 때 양과 늑대의 수를 찾는 알고리즘을 구현해라..

	울타리 안의 양과 늑대를 고려해야되므로 BFS를 사용하여 탐색하면서 양과 늑대의 수를 계산하여
	전체의 늑대와 양의 수에서 빼는 알고리즘 구현..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
char str[251];
char board[251][251];
bool check[250][250];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int sheep;// 전체 양의 수를 세기위해..
int wolf; // 전체 늑대의 수를 세기위해..

typedef struct _pos {
	int h, y;
	char c;
}pos;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'v') wolf++; // 전체 늑대의 수..
			if (board[hang][yal] == 'o') sheep++;  // 전체 양의 수..
		}
	}

	for (int hang = 0; hang < N; hang++) { // 마당을 돌면서 양 or 늑대가 나타나면 BFS탐색..
		for (int yal = 0; yal < M; yal++) {
			if (!check[hang][yal]) {
				if (board[hang][yal] == 'v' || board[hang][yal] == 'o') {
					BFS(hang, yal);
				}
			}
		}
	}

	printf("%d %d\n", sheep, wolf);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal, board[hang][yal] }));
	int cnt_sheep = 0; // 울타리안의 양의 수를 고려하기위해
	int cnt_wolf = 0; // 울타리 안의 늑대의 수를 고려하기위해..


	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		if (p.c == 'v') cnt_wolf++; 
		if (p.c == 'o') cnt_sheep++;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

			if (board[newY][newX] == '.' && !check[newY][newX]) { // 빈곳일 때
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
			if (board[newY][newX] == 'v' && !check[newY][newX]) { // 늑대일 때..
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
			if (board[newY][newX] == 'o' && !check[newY][newX]) { // 양일 때..
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
		}
	}

	if (cnt_wolf >= cnt_sheep) sheep -= cnt_sheep; // 늑대의 수가 크거나 같으면 전체의 양의 수에서 울타리 안의 양의 수를 뺀다..
	else wolf -= cnt_wolf; // 양의 수가 더 많으면 전체의 늑대의 수에서 울타리 안의 늑대의 수를 뺀다..
}