#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N;

// �����ʿ� 0 �� ������ ���ؼ��� 2, 5�� �ʿ��ϴ� �� �߿��� ���� ���� �����ϸ�
// �����ʿ� 0�� � ���� �Ǵ��� �� �ִ�.(���μ� ���ظ� ���� 2, 5�� ������ ���� �����ش�)
int main() {
	scanf("%d", &N);
	for (int fac, i = 0; i < N; i++) {
		int two = 0, five = 0;
		scanf("%d", &fac);
		for (int j = 2; j <= fac; j *= 2) {
			two += fac / j;
		}
		//���� ��� 25�� 5�� 2���̴� ���� ���� N�� 30�̸� 25�� j == 5 �϶� 5�� �ϳ� �÷����ǰ� j == 25�� �� �� �÷����ȴ�.
		for (int j = 5; j <= fac; j *= 5) {
			five += fac / j;
		}
		printf("%d\n", min(two, five));
	}
	return 0;
}