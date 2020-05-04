/*
	https://www.acmicpc.net/problem/16562
	���Ͽ����ε带 Ȱ���Ͽ� ģ���� ��ʹ� ����� ���� �� ��������� 
	���Ͽµ� ������ �θ� �ٲ��ִ� �˰��� ����(�������� ���ȴ�..)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M, K;
int parent[10001]; 
int cost[10001]; // ������ ����� ����Ǳ� ���� ���..
bool check[10001]; // ������� �̾Ƴ�������..
int result;

typedef struct _pos {
	int A, B;
}pos;
vector<pos> Vec;

int _find(int x) { // ���ε带 ���� ������ �θ� ã�´�..
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


		if (a_head != b_head) { //���� ������ �ƴϸ� ���Ͽ��� �Ѵ�..
			if (cost[a_head] >= cost[b_head]) {

				for (int i = 1; i <= N; i++) { // �ּҰ��� ���ϱ����� a_head�� b_head�� ���ؼ� ���� ������ ������ �θ� ��ιٲ۴�.
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
	for (int i = 1; i <= N; i++) { // ������ �θ�鸸�� ã�´�.(������ �θ���� ���� �ּ��� ����� �����������Ƿ�)
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