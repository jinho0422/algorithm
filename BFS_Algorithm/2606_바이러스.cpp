#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
bool check[101];
int result;

vector<int> Vec[101];

void BFS(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}

	BFS(1);
	printf("%d\n", result);

	return 0;
}

void BFS(int start) {
	queue<int> Q;
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			if (!check[Vec[p][s]]) {
				check[Vec[p][s]] = true;
				Q.push(Vec[p][s]);
				result++;
			}
		}
	}
}