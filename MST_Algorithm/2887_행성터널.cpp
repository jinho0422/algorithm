/*
	https://www.acmicpc.net/problem/2887
	N���� �༺���� �̷����ְ� �� �༺�� ȿ�������� �����ϱ� ���ؼ� �༺�� �����ϴ� �ͳ��� ��������Ѵ�.
	�༺�� 3���� ��ǥ���� �� ������ �����ϸ� �ȴ�. �� �༺ x, y, z�� �ͳη� ������ �� ��� ����� ������ x y z�� ���� ���� ���밪�� �ּ��̴�.
	�ͳ��� �� N -1���Ǽ��ؼ� ��� �༺�� ���� ����ǰ� �Ϸ����Ѵ�. �ּҺ���� ���ϴ� �˰��� ����

	N���� �༺���� �� N -1�ͳ��� �Ǽ��ؼ� ��� �༺�� ���� ����ǰ� �Ϸ��� �ϹǷ� ���Ͽ�����Ʈ�� ����Ͽ�
	��� �༺�� ����� �� �ֵ��� MST�� Ȱ���Ͽ� �˰��� ����..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N;
int parent[100001];// ���Ͽ� ����Ʈ�� ����ϱ� ����..
int result;
int cnt;

typedef struct _pos1 { // ������ x, y, z��  �� �༺��ȣ�� �ֱ����� struct 
	int n, b;
}pos1;

bool cmp (const pos1 &p, const pos1 &q) { // x, y, z�������� �༺������ �ּ� ����� �����ϱ� ���� ���� struct
	return p.b > q.b;
}
pos1 X[100001];// �� �༺�� ��ȣ�� x��ǥ
pos1 Y[100001];// �� �༺�� ��ȣ�� y��ǥ
pos1 Z[100001];// �� �༺�� ��ȣ�� z��ǥ

typedef struct _pos { // �༺���� �༺ ��ȣ�� �ּ� ����� ���� �� �ִ� struct 
	int x, y, W;
}pos;

bool cmp1(const pos &p, const pos &q) { // ���;ȿ� �ִ� �ּҺ���� ������������ �����ϱ� ���� struct
	return p.W < q.W;
}
vector<pos> Vec;

int find_(int x) { // �ڱ� �ڽ��� �ֻ����� ã���ִ� find �Լ�
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) { // ���Ͽ� ���ε带 ���ֱ� ���� ���ʷ� �ڱ� �ڽ��� �ֻ�����..(�迭�� ������ �ִ� ���� �ڱ� �ֻ��� ��ġ)
		parent[i] = i;
	}

	for (int a, b, c, i = 1; i <= N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		X[i] = { i, a };
		Y[i] = { i, b };
		Z[i] = { i, c };
	}
	sort(X + 1, X + N + 1, cmp);
	sort(Y + 1, Y + N + 1, cmp);
	sort(Z + 1, Z + N + 1, cmp);

	for (int i = 1; i < N; i++) { // ������ �༺�� x, y, z�� �ٸ� �Ǽ� �ּҰ��� �־��ش�.
		Vec.push_back(pos({ X[i].n, X[i + 1].n, abs(X[i].b - X[i + 1].b) }));
		Vec.push_back(pos({ Y[i].n, Y[i + 1].n, abs(Y[i].b - Y[i + 1].b) }));
		Vec.push_back(pos({ Z[i].n, Z[i + 1].n, abs(Z[i].b - Z[i + 1].b) }));
	}

	sort(Vec.begin(), Vec.end(), cmp1); // MST�� ����ϱ� ���� ����..

	for (int s = 0; s < Vec.size(); s++) { // ������ size��ŭ ���鼭 ���Ͽ����ش�..
		int a_head = find_(Vec[s].x);
		int b_head = find_(Vec[s].y);

		if (a_head != b_head) {// find�� ���־��� �� �ֻ��� ���� �ٸ��� 
			parent[a_head] = b_head; // �����ش�..
			result += Vec[s].W;// �ٸ��Ǽ� ����� �����ش�..
			cnt++;// �Ǽ��� �ٸ��� �����ش�..
			if (cnt == N - 1) break;// ��� �༺�� ����Ǵ� �ٸ��� ��������� break.
		}
	}
	printf("%d\n", result);
	return 0;
}