#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int N;
char str[26];
int board[26][26];
bool check[26][26];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

vector<int> Vec;

void BFS(int hang, int yal);

int main() {
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", &str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] -'0';
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal);
			}
		}
	}
	sort(Vec.begin(), Vec.end());
	int sz = Vec.size();
	printf("%d\n", sz);
	for (int s = 0; s < sz; s++) {
		printf("%d\n", Vec[s]);
	}

	return 0;
}

void BFS(int hang, int yal) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int num = 1;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				num++;
				Q.push(pos({ newY, newX }));
			}
		}
	}
	Vec.push_back(num);
}