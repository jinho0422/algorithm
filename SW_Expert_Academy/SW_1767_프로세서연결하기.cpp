#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
using namespace std;

int N;
int board[12][12];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result[14];

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec;

void DFS(int depth,int chip, int ff, int sum);

int main() {
	//freopen("test.txt", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		Vec.clear();
		scanf("%d", &N);
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
				if (board[hang][yal] == 1) {
					if (hang == 0 || yal == 0 || hang == N - 1 || yal == N - 1) continue;
					Vec.push_back(pos({ hang, yal }));
				}
			}
		}
		for (int i = 1; i <= Vec.size(); i++) result[i] = 987654321;
		DFS(0, 0, Vec.size(), 0);
		for (int i = Vec.size(); i >= 0; i--) {
			if (result[i] == 987654321) continue;
			printf("#%d %d\n", t, result[i]);
			break;
		}
	}
	return 0;
}

int solve(int d, int i) {
	
	int H = Vec[i].h, Y = Vec[i].y;
	int cnt = 0;
	while (1) {
		int newY = H + dirY[d];
		int newX = Y + dirX[d];

		if ((newY == 0 || newY == N - 1 || newX == 0 || newX == N - 1) && board[newY][newX] == 0) {
			cnt++;
			return cnt;
		}
		if (board[newY][newX] == 1) return 0;
		if (board[newY][newX] == 0) {
			cnt++;
			H = newY, Y = newX;
		}
	}
}

void DFS(int depth, int chip, int ff, int sum) {
	if (depth <= ff) {
		if (result[chip] > sum) result[chip] = sum;
		if (depth == ff) return;
	}
	for (int dir = 0; dir < 4; dir++) {
		int cnt = solve(dir, depth);

		if (cnt != 0) {
			int H = Vec[depth].h, Y = Vec[depth].y;
			for (int i = 0; i < cnt; i++) {
				int newY = H + dirY[dir];
				int newX = Y + dirX[dir];
				board[newY][newX] = 1;
				H = newY, Y = newX;
			}
			DFS(depth + 1, chip + 1, ff, sum + cnt);
			H = Vec[depth].h, Y = Vec[depth].y;
			for (int i = 0; i < cnt; i++) {
				int newY = H + dirY[dir];
				int newX = Y + dirX[dir];
				board[newY][newX] = 0;
				H = newY, Y = newX;
			}
		}
	}
	DFS(depth + 1, chip, ff, sum);
}