#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
int board[21][21];
bool check[21][21];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int home;
int result;

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;
void BFS(int hang, int yal);

int main() {
	freopen("test.txt", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		home = 0;
		result = 0;
		scanf("%d %d", &N, &M);
		
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
				if (board[hang][yal] == 1) home++;
			}
		}
		if (home * M - (N * N + (N - 1) * (N - 1)) >= 0) printf("#%d %d\n", t, home);
		else {
			for (int hang = 0; hang < N; hang++) {
				for (int yal = 0; yal < N; yal++) {
					memset(check, false, sizeof(check));
					BFS(hang, yal);
				}
			}
			printf("#%d %d\n", t, result);
		}
		
	}

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	int time = 1;
	int checkHome = board[hang][yal];
	Q.push(pos({ hang, yal}));

	while (!Q.empty()) {
		int sz = Q.size();
		int cnt = checkHome * M - (time * time + (time - 1) * (time - 1));
		if (cnt > 0) if (result < checkHome) result = checkHome;
		

		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || check[newY][newX]) continue;

				if (board[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX}));
				}
				if (board[newY][newX] == 1 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX}));
					checkHome++;
				}
			}
		}
		time++;
	}
}