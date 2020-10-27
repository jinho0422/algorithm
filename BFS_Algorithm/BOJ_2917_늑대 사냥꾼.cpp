#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

int N, M;
char str[501];
char board[501][501];
int maxD[501][501];
bool check[501][501];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : �����̴� ���� �������� �ּ� �Ÿ��� ����..
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt < q.cnt;
	}
};
queue<pos> tree; // ������ �ִ� ��ġ
vector<pair<int, int>> st; // ������
priority_queue<pos, vector<pos>, cmp> Q;


void BFS();
int solve(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'V') st.push_back({ hang, yal });
			else if (board[hang][yal] == '+') {
				check[hang][yal] = true;
				tree.push(pos({ hang, yal }));
			}
		}
	}
	BFS();
	memset(check, false, sizeof(check));
	printf("%d\n", solve(st[0].first, st[0].second));

	return 0;
}
// ������ ������ �������� ��ġ�� �ּҰ��� ����ū �� ã��.. 
void BFS() {
	while (!tree.empty()) {
		int sz = tree.size();
		for (int s = 0; s < sz; s++) {
			pos p = tree.front();
			tree.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || check[newY][newX]) continue;

				if (!check[newY][newX]) {
					check[newY][newX] = true;
					maxD[newY][newX] = maxD[p.h][p.y] + 1;
					tree.push(pos({ newY, newX }));
				}
			}
		}
	}
}
// ������ �Ÿ��� �����̸鼭 �������� �Ÿ��� ���� �ּҿ��� ���� ã��..
int solve(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal, maxD[hang][yal] }));
	int result = 987654321;

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		result = min(result, p.cnt);
		if (board[p.h][p.y] == 'J') return result;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || check[newY][newX]) continue;
			
			if (!check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, maxD[newY][newX] }));
			}
		}
	}
}