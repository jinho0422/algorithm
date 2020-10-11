#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int r, c, k;
int board[101][101];
int szH, szY;
int ssH, ssY;
int tmp[101];

typedef struct _pos {
	int h, y;
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		if (p.y == q.y) return p.h > q.h;
		return p.y > q.y;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;

int main() {
	scanf("%d %d %d", &r, &c, &k);
	for (int hang = 1; hang <= 3; hang++) {
		for (int yal = 1; yal <= 3; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}

	szH = 3; szY = 3;

	for (int t = 0; t <= 100; t++) {
		if (board[r][c] == k) {
			printf("%d\n", t);
			return 0;
		}

		if (szH >= szY) {
			ssH = szH;
			ssY = szY;
			szH = 0; szY = 0;
			for (int hang = 1; hang <= ssH; hang++) {
				szH++;
				for (int yal = 1; yal <= ssY; yal++) {
					if (board[hang][yal] == 0) continue;
					tmp[board[hang][yal]]++;
					board[hang][yal] = 0;
				}
				for (int i = 1; i <= 100; i++) {
					if (tmp[i] != 0) {
						Q.push(pos({ i, tmp[i] }));
						tmp[i] = 0;
					}
				}
				int sz = Q.size();
				if (sz > 50) sz = 50;
				if (szY < sz * 2) szY = sz * 2;
				for (int s = 0; s < sz; s++) {
					pos p = Q.top();
					Q.pop();
					board[szH][s + s + 1] = p.h;
					board[szH][s + s + 2] = p.y;
				}
				while (!Q.empty()) Q.pop();
			}
		}

		else {
			ssH = szH;
			ssY = szY;
			szH = 0; szY = 0;
			for (int yal = 1; yal <= ssY; yal++) {
				szY++;
				for (int hang = 1; hang <= ssH; hang++) {
					if (board[hang][yal] == 0) continue;
					tmp[board[hang][yal]]++;
					board[hang][yal] = 0;
				}
				for (int i = 1; i <= 100; i++) {
					if (tmp[i] != 0) {
						Q.push(pos({ i, tmp[i] }));
						tmp[i] = 0;
					}
				}
				int sz = Q.size();
				if (sz > 50) sz = 50;
				if (szH < sz * 2) szH = sz * 2;
				for (int s = 0; s < sz; s++) {
					pos p = Q.top();
					Q.pop();
					board[s + s + 1][szY] = p.h;
					board[s + s + 2][szY] = p.y;
				}
				while (!Q.empty()) Q.pop();
			}
		}
	}

	printf("-1\n");
	return 0;
}