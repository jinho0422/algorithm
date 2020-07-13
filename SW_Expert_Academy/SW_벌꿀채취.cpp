#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int board[20][20];
bool check[20][20];
int dirY[4] = { 1, 1, -1, -1 };
int dirX[4] = { 1, -1, -1, 1 };
int disert[400];
int result;

void solve(int hang, int yal, int depth, int dir, int fh, int fy);

int main() {
	freopen("test.txt", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		result = 0;
		scanf("%d %d %d", &N);
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
			}
		}
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if ((hang == 0 && yal == 0) || (hang == 0 && yal == N - 1) || (hang == N - 1 && yal == 0) || (hang == N - 1 && yal == N - 1)) continue;
				disert[0] = board[hang][yal];
				check[hang][yal] = true;
				solve(hang, yal, 0, 0,hang, yal );
				disert[0] = 0;
				check[hang][yal] = false;			
			}
		}
		if (result == 0) printf("#%d -1\n", t);
		else printf("#%d %d\n", t, result);

	}

	return 0;
}

void solve(int hang, int yal, int depth, int dir, int fh, int fy) {
	if (depth != 0 && hang == fh && yal == fy) {
		if (result < depth) result = depth;
		return;
	}

	int newY = hang + dirY[dir];
	int newX = yal + dirX[dir];

	if (newY >= 0 && newY < N && newX >= 0 && newX < N) {
		if (!check[newY][newX]) {
			bool flag = false;
			for (int i = 0; i < depth; i++) {
				if (desert[i] == board[newY][newX]) {
					flag = true;
					//return;
				}
			}
			if (!flag) {
				check[newY][newX] = true;
				solve(newY, newX, depth + 1, dir, fh, fy);
				check[newY][newX] = false;
			}
		}
		else if (check[newY][newX]) {
			if (newY == fh && newX == fy) {
				solve(newY, newX, depth + 1, dir, fh, fy);
			}
		}
	}

	int ndir = dir + 1;

	newY = hang + dirY[ndir];
	newX = yal + dirX[ndir];

	if (ndir < 4) {
		if (newY >= 0 && newY < N && newX >= 0 && newX < N) {
			if (!check[newY][newX]) {
				flag = false;

				for (int i = 0; i < depth; i++) {
					if (desert[i] == board[newY][newX]) {
						flag = true;
					}
				}
				if (!flag) {
					check[newY][newX] = true;
					solve(newY, newX, depth + 1, dir, fh, fy);
					check[newY][newX] = false;
				}
			}

			else if (check[newY][newX]) {
				if (newY == fh && newX == fy) {
					solve(newY, newX, depth + 1, dir, fh, fy);
				}
			}
		}
	}

	
}