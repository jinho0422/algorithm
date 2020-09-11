#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int N, M;
bool check[1001];

vector<int> Vec[1001];

void BFS(int start);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b); // 방향이 없기때문에
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}
	int result = 0; // 결과값
	for (int i = 1; i <= N; i++) { // 1~ N 까지 돌면서 만약 방문을 하지 않았다면 그 부분부터 갈 수있는 정점을 모두 방문처리한다.
		if (!check[i]) {
			BFS(i);
			result++;
		}
	}
	//출력
	printf("%d\n", result);
	return 0;
}

void BFS(int start) {
	check[start] = true;
	queue<int> Q;
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];
			if (!check[first]) {
				check[first] = true; // 방문하지 않았다면 방문
				Q.push(first);
			}
		}
	}
}