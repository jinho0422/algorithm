#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, V, start;
int board[20001];
bool check[20001];

typedef struct _pos {
	int B, W;
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.W > q.W;
	}
};


vector<pos> Vec[20001];
priority_queue<pos, vector<pos>, cmp> Q;

void BFS();

int main() {
	scanf("%d %d %d", &N, &V, &start);
	for (int a, b, w, i = 0; i < V; i++) {
		scanf("%d %d %d", &a, &b, &w);
		Vec[a].push_back(pos({ b, w }));
	}
	for (int i = 1; i <= N; i++) {
		if (i == start) continue;
		board[i] = 2147000000;
	}

	BFS();
	
	
	for (int i = 1; i <= N; i++) {
		if (board[i] == 2147000000) printf("INF\n");
		else printf("%d\n", board[i]);
	}

	return 0;
}

void BFS() {
	Q.push(pos({ start, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		if (p.W > board[p.B]) continue;
		int sz = Vec[p.B].size();
		for (int s = 0; s < sz; s++) {
			if (board[Vec[p.B][s].B] > p.W + Vec[p.B][s].W) {
				board[Vec[p.B][s].B] = p.W + Vec[p.B][s].W;
				Q.push(pos({ Vec[p.B][s].B, p.W + Vec[p.B][s].W }));
			}
		}
	}
}