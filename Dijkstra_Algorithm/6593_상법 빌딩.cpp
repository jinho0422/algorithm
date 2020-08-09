#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int L, N, M;
char str[31];
char board[31][31][31];
int dij_board[31][31][31];
int dirY[6] = { 0, -1, 1, 0, 0, 0 };
int dirX[6] = { 1, 0, 0, -1, 0, 0 };
int dirZ[6] = { 0, 0, 0, 0, 1, -1 };

typedef struct _pos {
	int z, h, y, t;
}pos;

pos start[1];
pos endd[1];

void BFS(int Z, int hang, int yal);

int main() {

	while (1) {
		scanf("%d %d %d", &L, &N, &M);
		if (L == 0 && N == 0 || M == 0) break;

		for (int he = 0; he < L; he++) {
			for (int hang = 0; hang < N; hang++) {
				scanf("%s", str);
				for (int yal = 0; yal < M; yal++) {
					board[he][hang][yal] = str[yal];
					dij_board[he][hang][yal] = INF;

					if (board[he][hang][yal] == 'S') {
						start[0] = { he, hang, yal };
						board[he][hang][yal] = '.';
					}
					else if (board[he][hang][yal] == 'E') {
						endd[0] = { he, hang, yal };
						board[he][hang][yal] = '.';
					}

				}
			}
		}

		BFS(start[0].z, start[0].h, start[0].y);
	}

	return 0;
}

void BFS(int Z, int hang, int yal) {
	dij_board[Z][hang][yal] = 0;
	queue<pos> Q;
	Q.push(pos({ Z, hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		if (p.z == endd[0].z && p.h == endd[0].h && p.y == endd[0].y) {
			printf("Escaped in %d minute(s).\n", p.t);
			return;
		}

		for (int dir = 0; dir < 6; dir++) {
			int newZ = p.z + dirZ[dir];
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newZ < 0 || newZ > L - 1 || newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newZ][newY][newX] == '.') {
				if (dij_board[newZ][newY][newX] > p.t + 1) {
					dij_board[newZ][newY][newX] = p.t + 1;
					Q.push(pos({ newZ, newY, newX, dij_board[newZ][newY][newX] }));
				}
			}
		}

	}
	printf("Trapped!\n");
}