#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M, H;
int board[101][101][101];
bool check[101][101][101];
int zero;
int dirY[6] = { -1, 0, 0, 1, 0, 0 };
int dirX[6] = { 0, -1, 1, 0, 0, 0 };
int dirZ[6] = { 0, 0, 0, 0, 1, -1 };

typedef struct _pos {
	int w, h, y;
}pos;

queue<pos> Q;

void BFS();

int main() {
	scanf("%d %d %d", &M, &N, &H);
	for (int h = 0; h < H; h++) {
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				scanf("%d", &board[h][hang][yal]);
				if (board[h][hang][yal] == 0) zero++;
				else if (board[h][hang][yal] == 1) {
					check[h][hang][yal] = true;
					Q.push(pos({ h, hang, yal }));
				}
			}
		}
	}

	BFS();
	return 0;
}

void BFS() {
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 6; dir++) {
				int newZ = p.w + dirZ[dir];
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newZ < 0 || newZ > H - 1 || newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newZ][newY][newX] == 0 && !check[newZ][newY][newX]) {
					check[newZ][newY][newX] = true;
					board[newZ][newY][newX] = 1;
					Q.push(pos({ newZ, newY, newX }));
					zero--;
				}
			}	
		}
		time++;
	}

	if (zero == 0) printf("%d\n", time -1);
	else printf("-1\n");
}