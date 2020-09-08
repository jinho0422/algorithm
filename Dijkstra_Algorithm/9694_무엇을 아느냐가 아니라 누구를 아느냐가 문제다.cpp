#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
int dij_board[22];
int link[22]; // 최적화된 결과값에서 연결관계를 가져오기위해.
bool flag;

typedef struct _pos {
	int B, W;
}pos;

bool cmp1(const pos& p, const pos& q) { // 사람관의 관계가 1, 2, 3, 4순으로 올 수 있게하려고
	return p.W < q.W;
}

vector<pos> Vec[21]; // 한사람과 연결된 사람의 번호와 그 관계의 차수를 넣는다.
queue<int> Q;
stack<int> S; // 결과값의 루트를 뽑아내기 위해..

void BFS(int start);

int main() {
	//입력
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		memset(link, 0, sizeof(link)); // 연결관계 초기화..
		for (int i = 1; i < M; i++) {
			dij_board[i] = INF;
		}
		for (int a, b, c, i = 0; i < N; i++) {
			scanf("%d %d %d", &a, &b, &c);
			Vec[a].push_back(pos({ b, c }));
			Vec[b].push_back(pos({ a, c }));
		}
		// 관계가 최측근부터 정렬될 수 있도록
		for (int i = 0; i < M; i++) {
			sort(Vec[i].begin(), Vec[i].end(), cmp1);
		}
		flag = false; // 만나야 하는 사람에게 도착했는지 여부.
		BFS(0);
		//출력
		printf("Case #%d: ", t);
		if (flag) {
			S.push(M - 1);
			while (1) {
				int s = S.top();
				if (s == 0) break;
				S.push(link[s]);
			}
			while (!S.empty()) {
				printf("%d ", S.top());
				S.pop();
			}
		}
		else printf("-1");
		printf("\n");
		for (int i = 0; i < M; i++) Vec[i].clear(); // 초기화
	}
	return 0;
}

void BFS(int start) {
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		if (p == M - 1) {
			flag = true; // 만나야하는 사람을 만나면 flag : true
		}
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s].B;
			int second = Vec[p][s].W;
			//다직스트라를 사용해서
			if (dij_board[first] > dij_board[p] + second) {
				dij_board[first] = dij_board[p] + second;
				Q.push(first);
				link[first] = p; // 만약 최소의 친밀도로 갈 수 있으면 link를 연결시킨다.
			}
		}
	}
}