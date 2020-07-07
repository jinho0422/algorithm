#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int T, N;
bool check[102];
bool flag;

vector<int> Vec[102];
queue<int> Q;

void BFS(int start);

int main() {
	//freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		//도착점에 도달했는지를 판단할 flag 초기화, 입력..Vec 각각에 갈 수 있는 지점을 저장..
		flag = false;
		scanf("%d %d", &T, &N);
		for (int a, b, s = 0; s < N; s++) {
			scanf("%d %d", &a, &b);
			Vec[a].push_back(b);
		}
		//BFS를 통해 갈 수 있는 곳을 visited하면서 도착점까지 가는지를 판단..
		BFS(0);
		//출력..
		if (flag) printf("#%d 1\n", t);
		else printf("#%d 0\n", t);
		//초기화..
		for (int s = 0; s < 100; s++) Vec[s].clear();
		while (!Q.empty()) Q.pop();
		memset(check, false, sizeof(check));
	}

	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		//도착점에 도달하면 flag로 도착점에 도달했다는 표시를 하고 함수를 빠져나온다.
		if (p == 99) {
			flag = true;
			return;
		}

		for (int s = 0; s < Vec[p].size(); s++) {
			if (!check[Vec[p][s]]) {
				check[Vec[p][s]] = true;
				Q.push(Vec[p][s]);
			}
		}
	}

}