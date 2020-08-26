#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
bool check[100002];
int result;

typedef struct _pos {
	int n, c;
}pos;

queue<pos> Q;

void BFS(int start);

int main() {
	result = 2147000000;
	scanf("%d %d", &N, &K);
	BFS(N);
	printf("%d\n", result);
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(pos({ start, 0 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		if (p.n == K) {
			if (result > p.c) {
				result = p.c;
				continue;
			}
		}

		if (p.n + 1 <= 100000) {
			if (!check[p.n + 1]) {
				check[p.n + 1] = true;
				Q.push(pos({ p.n + 1, p.c + 1 }));
			}
		}
		if (p.n - 1 >= 0) {
			if (!check[p.n - 1]) {
				check[p.n - 1] = true;
				Q.push(pos({ p.n - 1, p.c + 1 }));
			}
		}
		if (p.n * 2 <= 100000) {
			if (!check[p.n * 2]) {
				check[p.n * 2] = true;
				Q.push(pos({ p.n * 2, p.c + 1 }));
			}
		}
	}
}