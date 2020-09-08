#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
char str[1501];
char board[1501][1501];
bool check[1501][1501];
int waterBoard[1501][1501]; // ���� ���ʿ� ���������� üũ�ϴ� �迭
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, time;
}pos;
vector<pos> swan; // ���� 2������ ���ִ´�.

struct cmp {
	bool operator() (pos p, pos q) {
		return p.time > q.time;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;
queue<pos> times;

int BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'L') {
				swan.push_back(pos({ hang, yal, 0}));
				board[hang][yal] = '.';
				times.push(pos({ hang, yal, 0 })); // �ٴٸ� time queue�� �ִ´�
				check[hang][yal] = true;
			}
			else if (board[hang][yal] == '.') {
				times.push(pos({ hang, yal, 0 }));// �ٴٸ� time queue�� �ִ´�
				check[hang][yal] = true;
			}
		}
	}
	int time = 1;
	while (!times.empty()) {
		int sz = times.size();
		for (int s = 0; s < sz; s++) {
			pos p = times.front();
			times.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// ���� ���� ����� queue�� ���鼭 waterBoard�� üũ�Ѵ�..
				if (board[newY][newX] == 'X' && !check[newY][newX]) {
					check[newY][newX] = true;
					waterBoard[newY][newX] = time;
					times.push(pos({ newY, newX }));
				}
			}
		}
		time++;
	}
	
	memset(check, false, sizeof(check)); // �ʱ�ȭ
	printf("%d\n",BFS(swan[0].h, swan[0].y)); // ���
	return 0;
}

// ������ ������ �ð��� üũ�ϴ� BFS
int BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		if (p.h == swan[1].h && p.y == swan[1].y) return p.time;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (!check[newY][newX]) {
				check[newY][newX] = true;
				if (p.time >= waterBoard[newY][newX]) {
					Q.push(pos({ newY, newX, p.time }));
				}
				else {
					Q.push(pos({ newY, newX, waterBoard[newY][newX] }));
				}
			}
		}
	}
}
