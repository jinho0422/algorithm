#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int start, endd;
bool check[101];

typedef struct _pos {
	int A, C;
}pos;

queue<pos> Q;
vector<int> Vec[101];

void BFS(int start);

int main() {
	scanf("%d %d %d %d", &N, &start, &endd, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}
	BFS(start);
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(pos({ start, 0 }));

	while (!Q.empty()) {

		pos p = Q.front();
		Q.pop();

		if (p.A == endd) {
			printf("%d\n", p.C);
			return;
		}
		
		int sz = Vec[p.A].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p.A][s];
			if (!check[first]) {
				check[first] = true;
				Q.push(pos({ first, p.C + 1 }));
			}
		}
	}
	printf("-1\n");
}