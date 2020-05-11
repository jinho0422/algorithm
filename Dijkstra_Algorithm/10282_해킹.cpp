/*
	https://www.acmicpc.net/problem/10282
	a가 다른 컴퓨터 b에 의존한다면, b가 감염되면 그로부터 일정 시간 뒤 a도 감염된다.
	마지막 감염되기 까지 걸리는 시간이므로 최소의 시간을 찾아야한다.
	다익스트라 알고리즘을 통해 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int n, d, c;
int dij[10001];

typedef struct _pos { 
	int A, S;
}pos;

typedef struct _pos1 {
	int B, co;
}pos1;

vector<pos> Vec[10001];
queue<pos1> Q;

void solve(int start);

int main() {
	int T; scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &n, &d, &c);
		for (int i = 1; i <= n; i++) { // 감염된 자신빼고 dij배열을 INF로 해준다.
			if (i == c) {
				dij[i] = 0;
				continue;
			}
			dij[i] = INF;
		}
		for (int a, b, s, i = 0; i < d; i++) { // 의존성 관계를 Vector를 통해 연결시켜준다.(Vec[감염시킬 수 있는 컴퓨터] = {감염될수 있는 컴퓨터, 시간}
			scanf("%d %d %d", &a, &b, &s);
			Vec[b].push_back(pos({ a, s }));
		}
		solve(c);
		int cnt = 0; // 감염 컴퓨터 갯수 
		int max_time = 0; // 최소의 시간을 구하기 위해 감염된 컴퓨터의 최대의 값을 찾아준다. 
		for (int i = 1; i <= n; i++) {
			if (dij[i] == INF) continue; //감염되지 않은 컴퓨터는 continue..
			cnt++;
			if (max_time < dij[i]) max_time = dij[i];
		}
		printf("%d %d\n", cnt, max_time);
		for (int i = 1; i <= n; i++) { // vector clear..
			Vec[i].clear();
		}
		
	}
	return 0;
}

void solve(int start) {
	Q.push(pos1({ start, 0 }));
	while (!Q.empty()) {
		pos1 p = Q.front();
		Q.pop();

		int sz = Vec[p.B].size(); // 감열시킬 수 있는 컴퓨터에서 감염될 수 있는 컴퓨터 갯수..
		for (int s = 0; s < sz; s++) { 
			int first = Vec[p.B][s].A;
			int second = Vec[p.B][s].S;

			if (dij[first] > p.co + second) { // 감염될 수 있는 컴퓨터가 감염시킬 수 있는 컴퓨터 시간 + 감열될 컴퓨터가 감열될 시간보다 크면 갱신..  
				dij[first] = p.co + second;
				Q.push(pos1({first, dij[first]}));
			}
		}
	}
}