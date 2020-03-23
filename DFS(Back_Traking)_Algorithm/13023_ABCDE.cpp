/*
	ķ������ �� N���� �����ϰ��ִ�. ������� 0������ N -1 ������ ��ȣ�� �Ű��� �ְ�,
	�Ϻ� ������� ģ���̴�. ������ ������ ���� ģ�� ���踦 ���� ���, A,B,C,D,E�� �����ϴ��� ���غ����� �Ѵ�.
	ex> A --> B --> C --> D --> E
	������ ���ǿ� �´� A, B, C, D, E�� �����ϸ� 1�� ������ 0 �� ����Ѵ�.

	������ ���� ���踦 ã������ DFS ��͸� Ȱ���Ͽ� �Ǵ��ϴ� �˰��� ����..
*/


#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
bool flag;
bool check[2001];

vector<int> Vec[2001]; // �ڽŰ� ģ���� ������� �ִ� vector..

void solve(int depth, int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a,b,i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b); // a�� b�� ģ���̸� b�� a�� ģ���̹Ƿ�..
		Vec[b].push_back(a);
	}

	for (int i = 0; i < N; i++) {
		solve(0, i); // �� ����� �������� 5���� ģ���� �̾��� �ִ��� �Ǵ��ϴ� �Լ�..
		if (flag) break; // 5���� ģ���� �̾��� ���谡 ������ break..
	}
	if (flag) printf("1\n");
	else printf("0\n");


	return 0;
}

void solve(int depth, int start) {
	if (flag) return; // 5���� ģ���� �̾��� ���谡 ������ return..

	if (depth == 5) { 
		flag = true; // ���谡 �����Ǹ� flag = true..
		return;
	}

	int sz = Vec[start].size();
	for (int s = 0; s < sz; s++) {
		int first = Vec[start][s];
		if (!check[first]) {
			check[first] = true;
			solve(depth + 1, first); // ���
			check[first] = false;
		}
	}
}