#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;
int line[11];
int result[11]; // ������� �����ϱ� ���� �迭
int N;

int main() {
	//�Է�
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &line[i]);
	}

	for (int i = 1; i <= N; i++) { // 1~N���� ������� ���鼭
		int left = 0; // ������ result�� 0�� ������ count���� ����..
		for (int j = 0; j < N; j++) {
			if (result[j] == 0) { 
				if (left == line[i]) { //���� left�� i�� ���ʿ� �ִ� ū ����� ������ ������
					result[j] = i; // ����� ����..
					break;
				}
				else left++; // �ƴϸ� left�� ū ����� �ִٰ� conut�Ѵ�.
			}
		}
	}
	//���
	for (int i = 0; i < N; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
}