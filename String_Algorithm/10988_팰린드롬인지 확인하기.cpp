#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

char str[102];

// ������ �յ��� ��Ȳ�� ���� �����ϴ� ���̹Ƿ� deque�� ���
deque<char> Q;

int main() {
	//�Է�
	scanf("%s", str);

	for (int s = 0; str[s] != '\0'; s++) {
		Q.push_back(str[s]);
	}
	bool flag = false;
	while (1) {
		// �Ӹ������ �ƴϰų� Q�� ����ų� 1���̸� �������´�
		if (flag == true || Q.size() == 0 || Q.size() == 1) break;
		char f = Q.front();
		Q.pop_front();
		char b = Q.back();
		Q.pop_back();
		//������ �յڸ� ��
		if (f == b) continue;
		else flag = true;
	}
	// ���
	if (flag) printf("0\n");
	else printf("1\n");

	return 0;
}