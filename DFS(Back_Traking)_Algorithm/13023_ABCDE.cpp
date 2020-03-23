/*
	캠프에는 총 N명이 참가하고있다. 사람들이 0번부터 N -1 번으로 번호가 매겨져 있고,
	일부 사람들은 친구이다. 오늘은 다음과 같은 친구 관계를 가진 사람, A,B,C,D,E가 존재하는지 구해보려고 한다.
	ex> A --> B --> C --> D --> E
	문제의 조건에 맞는 A, B, C, D, E가 존재하면 1을 없으면 0 을 출력한다.

	다음과 같은 관계를 찾기위해 DFS 재귀를 활용하여 판단하는 알고리즘 구현..
*/


#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
bool flag;
bool check[2001];

vector<int> Vec[2001]; // 자신과 친구인 사람들을 넣는 vector..

void solve(int depth, int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a,b,i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b); // a와 b가 친구이면 b와 a도 친구이므로..
		Vec[b].push_back(a);
	}

	for (int i = 0; i < N; i++) {
		solve(0, i); // 한 사람을 기준으로 5명의 친구가 이어져 있는지 판단하는 함수..
		if (flag) break; // 5명의 친구가 이어진 관계가 있으면 break..
	}
	if (flag) printf("1\n");
	else printf("0\n");


	return 0;
}

void solve(int depth, int start) {
	if (flag) return; // 5명의 친구가 이어진 관계가 있으면 return..

	if (depth == 5) { 
		flag = true; // 관계가 형성되면 flag = true..
		return;
	}

	int sz = Vec[start].size();
	for (int s = 0; s < sz; s++) {
		int first = Vec[start][s];
		if (!check[first]) {
			check[first] = true;
			solve(depth + 1, first); // 재귀
			check[first] = false;
		}
	}
}