#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int numbers[10001];
int maxNum;

int main() {
	//�Է�
	int N; scanf("%d", &N);
	
	for (int num, s = 0; s < N; s++) {
		scanf("%d", &num);
		//���� �ְ� ����..
		if (maxNum < num) maxNum = num;
		// ���� ���� ����..
		numbers[num]++;
	}
	// 1���� �ְ����� ���� ������ ���..
	for (int s = 1; s <= maxNum; s++) {
		for (int i = 0; i < numbers[s]; i++) {
			printf("%d\n", s);
		}
	}

	return 0;
}