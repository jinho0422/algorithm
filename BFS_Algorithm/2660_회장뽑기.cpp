#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, a, b;
bool check[51];
int result;

typedef struct _pos {
	int n, c; // n : 번호, c : 몇번으로 모든 친구가 연결되는지
}pos;
//출력을 위한 정렬(최소의 연결로 같으면 앞순번부터 정렬)
bool cmp(const pos& p, const pos& q) {
	if (p.c == q.c) return p.n < q.n;
	return p.c < q.c;
}

vector<pos> link; // 결과값을 가지고 있는 vector
vector<int> Vec[51]; // 친구관계를 가지고 있는 vector
queue<int> Q;

void BFS(int start);

int main() {
	//입력
	scanf("%d", &N);
	while (1) {
		scanf("%d %d", &a, &b);
		if (a == -1 && b == -1) break;
		Vec[a].push_back(b); // a와 b가 친구면 b와 a도 친구인 양뱡관계
		Vec[b].push_back(a);
	}
	//각 회원수만큼 BFS를 돌면서 몇번만에 친구연결이 가능한지 link결과값에 넣는다.
	for (int i = 1; i <= N; i++) {
		BFS(i);
		//초기화
		while (!Q.empty()) Q.pop();
		memset(check, false, sizeof(check));
	}
	// 정렬
	sort(link.begin(), link.end(), cmp);
	// 출력
	for (int s = 0; s < link.size(); s++) {
		if (link[0].c == link[s].c) result++;
		else break;
	}
	printf("%d %d\n", link[0].c, result);
	for (int i = 0; i < result; i++) {
		printf("%d ", link[i].n);
	}
	printf("\n");
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);
	int time = 0; // 몇번의 연결로 친구가 되는지 판단하는 변수
	int cnt = 1; // 몇명이 연결되어있는지 판단하는 편수
	while (!Q.empty()) {
		int qsz = Q.size();
		for (int i = 0; i < qsz; i++) {
			int p = Q.front();
			Q.pop();
			int vsz = Vec[p].size();
			for (int s = 0; s < vsz; s++) {
				if (!check[Vec[p][s]]) {
					check[Vec[p][s]] = true;
					Q.push(Vec[p][s]);
					cnt++;
					if (cnt == N) { // 모든 회원이 연결되어있으면 결과값을 넣고 return.
						time++;
						link.push_back(pos({ start, time }));
						return;
					}
				}
			}
		}
		time++;
	}
}