#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
// 연락을 받은 사람을 check하는 배열
bool check[102];
// 연락을 하는 사람으로부터 받는 사람을 넣는 vector
vector<int> Vec[102];
// 각각의 연락시기에 연락을 받는 사람의번호를 넣는 queue
queue<int> Q;

int BFS(int start);

int main() {
	//freopen("test.txt", "r", stdin);
	//입력
	for (int t = 1; t <= 10; t++) {
		scanf("%d %d", &N, &M);

		for (int a, b, i = 0; i < N; i+=2) {
			scanf("%d %d", &a, &b);
			Vec[a].push_back(b);
		}
		// BFS를 통해 처음 연락을 취하는 사람으로부터 마지막 연락을 받는 사람까지 찾는다.
		int max_result = BFS(M);
		//출력
		printf("#%d %d\n", t, max_result);
		//초기화
		memset(check, false, sizeof(check));
		for (int i = 0; i < 102; i++) Vec[i].clear();
		while (!Q.empty()) Q.pop();
	}
	return 0;
}

int BFS(int start) {
	check[start] = true;
	Q.push(start);
	int result = 0;
	while (!Q.empty()) {
		result = 0;
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			// 연락을 받은 시기에 사람으로부터 최대의 번호를 뽑아낸다..
			if (result < p) result = p;

			//연락을 하는 사람으로부터 받는 사람이 받지않았던 사람이면 연락을 하면서 queue에 넣는다.
			int vecSz = Vec[p].size();
			for (int i = 0; i < vecSz; i++) {
				int arrive = Vec[p][i];
				if (!check[arrive]) {
					check[arrive] = true;
					Q.push(arrive);
				}
			}
		}
	}
	return result;
}