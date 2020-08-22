#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;

// map을 통해 value의 빈도수와 나온 순서를 저장하기위한 struct
typedef struct _pos {
	int cnt, f;
}pos;
// vector를 통해 값과 빈도수 나온 순서를 저장하기 위한 strcut
typedef struct _pos1 {
	int a, b, c;
}pos1;
// 빈도를 내림차순으로정렬 만약 빈도가 같다면 먼저 나온 순서대로 정렬..
bool cmp (const pos1& p, const pos1& q) { 
		if (p.b == q.b) return p.c < q.c;
		else return p.b > q.b;
};

map<int, pos> m;
map<int, pos>::iterator iter; 
vector<pos1> Vec;

int main() {
	//입력
	scanf("%d %d", &N, &C);
	int order = 0; // 나온 순서를 저장하기위해
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		m[a].cnt++;
		if (m[a].cnt == 1) m[a].f = order++; // 만약 처음 나왔다면 나온 순서를 저장..
	}
	// map m을 돌면서 Vector에저장
	for (iter = m.begin(); iter != m.end(); iter++) {
		Vec.push_back(pos1({ iter->first, iter->second.cnt, iter->second.f }));
	}
	// 빈도에 따라 정렬..
	sort(Vec.begin(), Vec.end(), cmp);
	// 출력
	for (int i = 0; i < Vec.size(); i++) {
		for (int j = 0; j < Vec[i].b; j++) {
			printf("%d ", Vec[i].a);
		}
	}
	printf("\n");
	return 0;
}