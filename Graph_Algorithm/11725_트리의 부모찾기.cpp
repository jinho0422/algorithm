#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;
int board[100001];
int check[100001];

// 방향성이 없는 노드들을 vector에 넣기위해
vector<int> Vec[100001];
// 부모를 통해 나온 자식들을 보관하기 위해..
queue<int> Q;

void solve(int start);

int main() {
	//입력
	scanf("%d", &N);
	for (int a, b, i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}
	solve(1);
	//출력
	for (int s = 2; s <= N; s++) {
		printf("%d\n", board[s]);
	}
	return 0;
}
// 최종부모인 1부터 시작..
void solve(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		// 부모를 통해 나온 자식들이 부모가 되어서 다음 자식들을 찾을 수 있도록..(섞이지않게) Q_size씩 돌려준다.
		int Qsz = Q.size();
		for (int s = 0; s < Qsz; s++) {
			int p = Q.front();
			Q.pop();
			// 각 부모에 대한 자식이 될 수 있는지를 판단해서 Q에 넣어준다.
			for (int i = 0; i < Vec[p].size(); i++) {
				int son = Vec[p][i];
				// 만약 check배열이 true 였다면 최종부모로부터 시작해서 먼저 자식으로 판명이 난 경우라고 생각.
				if (!check[son]) {
					check[son] = true;
					Q.push(son);
					board[son] = p;
				}
			}
		}
	}
}