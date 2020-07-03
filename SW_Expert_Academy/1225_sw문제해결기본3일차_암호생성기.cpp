#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

bool flag;
// front���� �ذ��� ���� back���� �־�� �ϱ� ������ deque ��� 
deque<int> Q;

int main() {
	//freopen("test.txt", "r", stdin);
	int T;
	for (int t = 1; t <= 10; t++) {
		//�Է°� deque�� �־��ش�.
		scanf("%d", &T);
		flag = false;
		for (int numbers, i = 0; i < 8; i++) {
			scanf("%d", &numbers);
			Q.push_back(numbers);
		}
		// �ݺ����� ���(�� ����Ŭ (1~5)�� ���鼭)�� �ϸ鼭 ���� ������� 0�����̸� ����Ŭ�� �����.
		while(!flag) {
			for (int i = 1; i <= 5; i++) {
				int p = Q.front();
				Q.pop_front();
				if (p - i <= 0) {
					flag = true;
					Q.push_back(0);
					break;
				}
				else {
					Q.push_back(p - i);
				}
			}
		}
		//��ºκ�
		printf("#%d ", t);
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop_front();
			printf("%d ", p);
		}
		printf("\n");
	}
	return 0;
}