/*
	https://www.acmicpc.net/problem/1715
	ī�幭���� 2���̻����� ���� �׻� ���� 2���� ��� ���ξ�� 
	�ּ����� �񱳸� �� �� �ִ�. �׷��⶧���� priority_queue�� ����Ͽ�
	�׻� ���� ���� ���� ���� �� �ְ��ϴ� �˰����� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>


using namespace std;

int N;
int result;

priority_queue<int, vector<int>, greater<int>> Q; // ���� ������ ���� �� �ִ� priority_queue

int main() {
	scanf("%d", &N);
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		Q.push(a);
	}

	if (Q.size() == 1) { // ���� ī�幭���� 1���̸� �񱳸� ���� �ʾƵ� �ǹǷ�..
		printf("0\n");
		return 0;
	}

	while (!Q.empty()) { // ī�幭���� 2�� �̻��̶��..
		if (Q.size() >= 2) {
			int p = Q.top();
			Q.pop();
			int q = Q.top();
			Q.pop(); // 2���� ī�带 ������ 
			result += (p + q); // ������� ++
			if (Q.size() != 0) Q.push(p + q); // ���� �ΰ��� ���� ���ؼ� queue�� �ٽ� �ִ´�.
			else break;
		}
	}
	printf("%d\n", result);
	return 0;
}