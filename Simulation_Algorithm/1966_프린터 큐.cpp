#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
typedef struct _pos {
	int n, f; // n : 문서가 있는 위치, f : 중요도
}pos;

bool cmp(const int& p, const int& q) { // 내림차순 정렬
	return p > q;
};

deque<pos> Q;
vector<int> Vec; // 중요도 저장vector..

int BFS();

int main() {
	//입력
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		for (int a, i = 0; i < N; i++) {
			scanf("%d", &a);
			Q.push_back(pos({ i, a }));
			Vec.push_back(a);
		}
		sort(Vec.begin(), Vec.end(), cmp); // 내림차순 정렬
		int result = BFS();
		//출력
		printf("%d\n", result);
		//초기화..
		while (!Q.empty()) Q.pop_back();
		Vec.clear();
	}
	return 0;
}

int BFS() {
	int time = 0; // 결과값
	int check = 0; // Vec의 중요도를 다루기위해..
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop_front();
		if(p.f == Vec[check] && p.n == M) { // 중요도도 같고 알고싶은 문서이면..
			time++;
			return time;
		}
		else if (p.f == Vec[check] && p.n != M) { // 중요도는 같지만 알고싶은 문서가 아닐시
			time++;
			check++;
		}
		else if (p.f != Vec[check]) { // 중요도가 같지 않을시..
			Q.push_back(pos({ p.n, p.f }));
		}
	}
}