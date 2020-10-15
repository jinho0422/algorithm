#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M, sh, sy, fh, fy;
char str[51];
char board[51][51];
bool nearG[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, G, n; // h : hang, y : yal, G : �����⸦ ���� Ƚ��, n : ������ ��ĭ�� ������ Ƚ��
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		if (p.G == q.G) return p.n > q.n;
		return p.G > q.G;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

typedef struct _pos1 {
	int a, b;
}pos1;
pos1 dij_board[51][51]; // ���ͽ�Ʈ�� ����ϱ����� a : �����⸦ ���� Ƚ�� b : ������ ���� ������ Ƚ��

void BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			dij_board[hang][yal] = { 2147000000, 2147000000 };
			if (board[hang][yal] == 'S') sh = hang, sy = yal;
			if (board[hang][yal] == 'F') fh = hang, fy = yal;	
		}
	}
	// ������ ��ĭ�� '.'�̸� nearG�迭�� ���� ������ ��ĭ�� �������� �� �Ǵ��� �� �ְ� �Ѵ�.
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 'g') {
				for (int dir = 0; dir < 4; dir++) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];
					if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
					if (board[newY][newX] == '.') nearG[newY][newX] = true;
				}
			}
		}	
	}
	board[fh][fy] = '.'; // ����ġ�� fh, fy�� �˰� ������ '.'���� �ٲ۴�..
	BFS(sh, sy);
	return 0;
}

void BFS(int hang, int yal) {
	dij_board[hang][yal] = { 0, 0 };
	Q.push(pos({ hang, yal, 0, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		//�ɿ� �����ϸ� ���
		if (p.h == fh && p.y == fy) {
			printf("%d %d\n", p.G, p.n);
			return;
		}

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
			// �����Ⱑ �ƴҶ�
			if (board[newY][newX] == '.') {
				// ������ ���϶�
				if (nearG[newY][newX]) {
					if (dij_board[newY][newX].a > p.G) {
						dij_board[newY][newX].a = p.G;
						Q.push(pos({ newY, newX, p.G, p.n + 1 }));
					}

					else if (dij_board[newY][newX].a == p.G) {
						if (dij_board[newY][newX].b > p.n + 1) {
							dij_board[newY][newX].b = p.n + 1;
							Q.push(pos({ newY, newX, p.G, p.n + 1 }));
						}
					}
				}
				// ������ ���� �ƴҶ�
				else {
					if (dij_board[newY][newX].a > p.G) {
						dij_board[newY][newX].a = p.G;
						Q.push(pos({ newY, newX, p.G, p.n}));
					}
					else if (dij_board[newY][newX].a == p.G) {
						if (dij_board[newY][newX].b > p.n) {
							dij_board[newY][newX].b = p.n;
							Q.push(pos({ newY, newX, p.G, p.n}));
						}
					}
				}
			}
			//�������϶�
			else if (board[newY][newX] == 'g') {
				if (dij_board[newY][newX].a > p.G + 1) {
					dij_board[newY][newX].a = p.G + 1;
					Q.push(pos({ newY, newX, p.G + 1, p.n }));
				}
				else if (dij_board[newY][newX].a == p.G + 1) {
					if (dij_board[newY][newX].b > p.n) {
						dij_board[newY][newX].b = p.n;
						Q.push(pos({ newY, newX, p.G + 1, p.n }));
					}
				}
			}
		}
	}
}