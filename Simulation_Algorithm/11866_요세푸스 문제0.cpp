#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, K;

deque<int> Q;

int main() {
	//�Է�
	scanf("%d %d", &N, &K);
	// qeque�� ���� �ڿ������� 1~ N���� �־��ش�(���̶�� �����ؼ� deque�� ���)
	for (int s = 1; s <= N; s++) {
		Q.push_back(s);
	}

	printf("<");
	// deque�� size�� 0�� �ɶ����� �����ִµ�
	while (1) {
		int p = 0;
		// K����� ������ �����ָ鼭
		for (int i = 0; i < K; i++) {
			p = Q.front();
			Q.pop_front();
			// ���������� front�� �ִ°� back���� �־����������� ������̶� �Ǹ��ϰ� ������ش�.
			if(i != K -1) Q.push_back(p);
		}
		//���� size�� 0�̸� ���̻� ���� �����ִ� ����� �����Ƿ� ����� �ϰ� ������.
		if (Q.size() != 0) printf("%d, ", p);
		else {
			printf("%d>\n", p);
			break;
		}
	}
	return 0;
}