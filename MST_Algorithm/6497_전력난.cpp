/*
	https://www.acmicpc.net/problem/6497
	MST������ ��ü�� ����ġ���� MST�� �̷���� ������� ���� ���� ������� ���� �� �ִ� �˰��� ����
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
int parent[200001]; // ���Ͽ� ���ε带 ��������..
int max_cost; // ���� �����־� ���̴� ��� ���� ������ ����
int result; // ��� ���� ������ �� ���̴� �ּ��� ��..

typedef struct _pos { // A == A��, B == B��, W == A --> B, B --> A�濡�� ���� ų �� ���̴� ���� ����ġ.
	int A, B, W;
}pos;

bool cmp(const pos& p, const pos& q) { // ����ġ�� �����ź��� �ϱ� ���� Vector ���� �Լ�..
	return p.W < q.W;
}

vector<pos> Vec;

int find_(int x) { //���Ͽ� ���ε��� ���ε�� �ڽ��� �θ� ã�� �Լ�..
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {

	while (1) {
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break; // N, M �� �Է��� 0�̸� break;;
		max_cost = 0; // �ʱ�ȭ..
		result = 0;

		for (int i = 0; i < N; i++) { // ���Ͽ� ���ε带 ���� �ڱ� �ڽ��� �κ��������� ����� ..
			parent[i] = i;
		}
		
		Vec.clear();
		for (int a, b, c, i = 0; i < M; i++) { // �Է�
			scanf("%d %d %d", &a, &b, &c);
			Vec.push_back(pos({ a, b, c }));
			max_cost += c; // ���� ���̰� �ִ� ���� ��..

		}
		sort(Vec.begin(), Vec.end(), cmp); // cmp�� Vec.tor ����..

		int cnt = 0;
		int sz = Vec.size();
		for (int s = 0; s < sz; s++) { // ���Ͽ� ���ε�..
			int a_head = find_(Vec[s].A);
			int b_head = find_(Vec[s].B);

			if (a_head != b_head) { // ���� ���ε��� a_head, b_head�� �ٸ��ٸ� ���Ͽ� ���ش�..
				parent[a_head] = b_head;
				result += Vec[s].W; // ������ �� ����ġ�� �����ش�..
				cnt++;
				if (cnt == N - 1) break; // MST(��� ������ �������� �� �������´�)
			}
		}
		printf("%d\n", max_cost - result);
	}
	return 0;
}