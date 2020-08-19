#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, K;
int board[100001];
int maxTemp;

int main() {
	// �� �µ��� -100 ~ 100 ���� �̹Ƿ� �ּҷ� ���� �� �ִ� ���� -100 * 100,000 �̴�.
	maxTemp = -2147000000;
	//�Է�
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	int sum = 0, cnt = 0; // sum : K���� ���� ��, cnt : K���� �Ǵ� ������ �ľ�
	for (int i = 0; i < N; i++) {
		// K���� �Ǹ� K�� ���� ���ְ� ���縦 �����ش�.
		if (cnt == K) {
			// ����
			if (maxTemp < sum) maxTemp = sum;
			sum -= board[i - cnt];
			sum += board[i];
			//����
			if (maxTemp < sum) maxTemp = sum;
		}
		// K���� �������� �ʾ����� �����ش�
		else {
			sum += board[i];
			cnt++;
		}
	}
	// ����
	if (maxTemp < sum) maxTemp = sum;
	printf("%d\n", maxTemp);
	return 0;
}