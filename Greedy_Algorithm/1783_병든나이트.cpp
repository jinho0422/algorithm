#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int result;


int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	// N(��)�� ũ�⿡ ���� N�� ũ�Ⱑ 1�̸� ����Ʈ�� ��, �Ʒ��� �̵��� �� �����Ƿ� ������� 1.
	if (N == 1) {
		result = 1;
	}
	// N�� ���� 2�̸� �� �Ʒ��� ������ �� �ִ� ũ�Ⱑ 1�̹Ƿ� ���������� ����Ʈ �Ǵ� ���� 2���̴�. �׸��� ������� 4�̻��� �Ѿ �� ����.
	else if (N == 2) {
		result = (M - 1) / 2 + 1;
		if (result > 4) result = 4;
	}
	// N�� ���� 3�̻��̸� M�� ���� ���� ���� M�� 6���� ũ�� ����Ʈ�� 4 ������ �� �����̰� ������ ����Ʈ�� 1ĭ���ϸ鼭 ������ �� �ִ�. 
	// M�� 6�����̸� ������ ����Ʈ�� �� ĭ���ϸ鼭 ������� �ִ�� 4���� �ۿ� �� �� �� ����.
	else {
		if (M > 6) {
			result = (M - 6) + 4;
		}
		else {
			result = (M - 1) + 1;
			if (result > 4) result = 4;
		}
	}
	printf("%d\n", result);
	return 0;
}

