#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
//�� ������ MST ���������� ������ ����ġ�� �������� �ʰ� ��� ��带 �湮�� �� �ִ� �ּ� ���� �湮 Ƚ���� ������ ���ϱ� ������ N -1�� ���̴�.
// MST�� �׻� ������ ������ N -1���̱� �����̴�.
int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		for (int a, b, i = 0; i < M; i++) {
			scanf("%d %d", &a, &b);
		}
		printf("%d\n", N - 1);
	}
	return 0;
}