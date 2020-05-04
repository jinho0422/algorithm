/*
	https://www.acmicpc.net/problem/16562
	유니온파인드를 활용하여 친구를 사귀는 비용이 작을 때 계속적으로 
	유니온된 집합의 부모를 바꿔주는 알고리즘 구현(생각보다 느렸다..)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M, K;
int parent[10001]; 
int cost[10001]; // 각각의 사람과 연결되기 위한 비용..
bool check[10001]; // 결과값을 뽑아내기위해..
int result;

typedef struct _pos {
	int A, B;
}pos;
vector<pos> Vec;

int _find(int x) { // 파인드를 통해 집합의 부모를 찾는다..
	if (parent[x] == x) return x;
	return parent[x] = _find(parent[x]);
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &cost[i]);
		parent[i] = i;
	}
	for (int a, b, i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b }));
	}
	int sz = Vec.size();
	for (int s = 0; s < sz; s++) {
		int a_head = _find(Vec[s].A);
		int b_head = _find(Vec[s].B);


		if (a_head != b_head) { //같은 집합이 아니면 유니온을 한다..
			if (cost[a_head] >= cost[b_head]) {

				for (int i = 1; i <= N; i++) { // 최소값을 구하기위해 a_head와 b_head를 비교해서 작은 값으로 집합의 부모를 모두바꾼다.
					if (parent[i] == a_head) parent[i] = b_head;
				}
				parent[a_head] = b_head;
			}
			else {
				for (int i = 1; i <= N; i++) {
					if (parent[i] == b_head) parent[i] = a_head;
				}
				parent[b_head] = a_head;
			}
		}
	}
	for (int i = 1; i <= N; i++) { // 집합의 부모들만을 찾는다.(집합의 부모들이 가장 최소의 비용을 가지고있으므로)
		if (!check[parent[i]]) check[parent[i]] = true;
	}
	for (int i = 1; i <= N; i++) {
		if (check[i]) {
			result += cost[i];
		}
	}

	if (result > K) printf("Oh no\n");
	else printf("%d\n", result);
	return 0;
}