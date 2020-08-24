#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
bool check[100003];
int parent[100003]; // 부모를 저장하기 위한 배열..
int result;
queue<int> Q;
vector<int> Vec; // 동생을 찾은 후 지금까지 왔던 경로를 찾기 위해.

void BFS(int start);

int main() {
	//입력
	scanf("%d %d", &N, &K);
	BFS(N);
	//출력
	printf("%d\n", result);
	for (int s = Vec.size() - 1; s >= 0; s--) {
		printf("%d ", Vec[s]);
	}
	printf("\n");
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		int sz = Q.size(); // 시간에 따른 움직임을 파악하기위해 Q.size만큼씩 돌린다.
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			if (p == K) { // 만약 동생을 찾으면
				Vec.push_back(K);
				int id = p; // 동생의 위치부터 부모를 찾기 시작하여 Vector에 넣는다.
				while (id != N) {
					Vec.push_back(parent[id]);
					id = parent[id];
				}
				return;
			}
			// +1, -1, * 2를 하면서 부모를 parent배열에 넣으며 간다..
			if (p + 1 <= 100000) {
				if (!check[p + 1]) {
					check[p + 1] = true;
					Q.push(p + 1);
					parent[p + 1] = p;
				}
			}
			if (p - 1 >= 0) {
				if (!check[p - 1]) {
					check[p - 1] = true;
					Q.push(p - 1);
					parent[p - 1] = p;
				}
			}
			if (p * 2 <= 100000) {
				if (!check[p * 2]) {
					check[p * 2] = true;
					Q.push(p * 2);
					parent[p * 2] = p;
				}
			}
		}
		result++;
	}
}