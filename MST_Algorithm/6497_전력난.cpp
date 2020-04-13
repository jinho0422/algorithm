/*
	https://www.acmicpc.net/problem/6497
	MST문제로 전체의 가중치에서 MST로 이루어진 결과값을 빼서 최종 결과값이 나올 수 있는 알고리즘 구현
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
int parent[200001]; // 유니온 파인드를 쓰기위해..
int max_cost; // 현재 켜져있어 쓰이는 모든 돈을 가지는 변수
int result; // 모든 집을 연결할 때 쓰이는 최소의 돈..

typedef struct _pos { // A == A집, B == B집, W == A --> B, B --> A길에서 불을 킬 때 쓰이는 돈의 가중치.
	int A, B, W;
}pos;

bool cmp(const pos& p, const pos& q) { // 가중치가 작은거부터 하기 위한 Vector 정렬 함수..
	return p.W < q.W;
}

vector<pos> Vec;

int find_(int x) { //유니온 파인드의 파인드로 자신의 부모를 찾는 함수..
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {

	while (1) {
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break; // N, M 의 입력이 0이면 break;;
		max_cost = 0; // 초기화..
		result = 0;

		for (int i = 0; i < N; i++) { // 유니온 파인드를 위해 자기 자신의 부분집합으로 만들기 ..
			parent[i] = i;
		}
		
		Vec.clear();
		for (int a, b, c, i = 0; i < M; i++) { // 입력
			scanf("%d %d %d", &a, &b, &c);
			Vec.push_back(pos({ a, b, c }));
			max_cost += c; // 현재 쓰이고 있는 돈의 합..

		}
		sort(Vec.begin(), Vec.end(), cmp); // cmp로 Vec.tor 정렬..

		int cnt = 0;
		int sz = Vec.size();
		for (int s = 0; s < sz; s++) { // 유니온 파인드..
			int a_head = find_(Vec[s].A);
			int b_head = find_(Vec[s].B);

			if (a_head != b_head) { // 만약 파인드한 a_head, b_head가 다르다면 유니온 해준다..
				parent[a_head] = b_head;
				result += Vec[s].W; // 합쳐줄 때 가중치를 더해준다..
				cnt++;
				if (cnt == N - 1) break; // MST(모든 정점을 연결했을 때 빠져나온다)
			}
		}
		printf("%d\n", max_cost - result);
	}
	return 0;
}