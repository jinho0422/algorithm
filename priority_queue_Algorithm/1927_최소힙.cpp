#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> Q;

int main() {
	//�Է�
	scanf("%d", &N);
	for (int in, s = 0; s < N; s++) {
		scanf("%d", &in);
		//���� �Է°��� 0�� ��
		if (in == 0) {
			// priority_queue�� size�� 0 �̸� 0�� ����ϰ� �ƴϸ� top()�� ���� ����ϰ� pop()�Ѵ�.
			if (Q.size() == 0) printf("0\n");
			else {
				int first = Q.top();
				Q.pop();
				printf("%d\n", first);
			}
		}
		// �Է°��� 0�� �ƴϸ� priority_queue�� �Է°��� push�Ѵ�.
		else {
			Q.push(in);
		}
	}
	return 0;
}