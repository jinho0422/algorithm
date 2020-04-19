/*
	https://www.acmicpc.net/problem/2696
	priority_queue�� ���������� ���������� ���� �߾Ӱ��� �̾Ƴ��� �˰��� ����..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int N;


priority_queue<int, vector<int>, less<int>>  max_Q; // �������� priority_queue ex> 5,4,3,2,1
priority_queue<int, vector<int>, greater<int>> min_Q; // �������� priority_queue ex> 1,2,3,4,5

vector<int> Vec; // ������� �����ϱ� ���� vector

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int a, i = 1; i <= N; i++) {
			scanf("%d", &a);
			if (max_Q.size() == min_Q.size()) max_Q.push(a); // �������� PQ�� �������� PQ�� ũ�Ⱑ ������ �������� PQ�� �־��ְ�
			else min_Q.push(a); // �ٸ��� �������� PQ�� �־��ش�.

			if (!max_Q.empty() && !min_Q.empty() && (max_Q.top() > min_Q.top())){ // ���� ���������� PQ�� top�� ���������� PQ�� top���� ũ��
				int p = max_Q.top(); max_Q.pop(); // ������ ��ġ�� �ٲ��ش�.. (�߾Ӱ��� �׻� max_Q�� top�̴�..)
				int q = min_Q.top(); min_Q.pop();
				min_Q.push(p);
				max_Q.push(q);		
			}
			if (i % 2 != 0) Vec.push_back(max_Q.top()); // Ȧ����°�� �� �߾Ӱ��� ����� Vector�� �־��ش�..
		}

		int sz = Vec.size();
		int cnt = 0;
		printf("%d\n", sz);
		for (int s = 0; s < sz; s++) {
			printf("%d ", Vec[s]);
			cnt++;
			if (cnt == 10) { // ��°��� 10���� ������ ���� �ٲ��ֱ�����..
				cnt = 0;
				printf("\n");
			}
		}
		printf("\n");
		//�ʱ�ȭ ����..
		while (!max_Q.empty()) max_Q.pop();
		while (!min_Q.empty()) min_Q.pop();
		Vec.clear();
	}
	return 0;
}