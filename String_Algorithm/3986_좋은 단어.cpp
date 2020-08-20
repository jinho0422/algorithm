#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

int N;
char str[100001];
int result;
stack<char> S; // stack�� ����� ������ ��ġ���� ��ġ�� ���� �Ǵ��ϱ� ����..

int main() {
	//�Է�
	scanf("%d", &N);
	for (int s = 0; s < N; s++) {
		scanf("%s", str);
		// stack�� size�� 0 �̸� str[i]�� �־��ְ� 0�� �ƴϸ� ���� �ܾ�� ���ϸ鼭 ������ pop �ƴϸ� push�� ���ش�.
		for (int i = 0; str[i] !='\0'; i++) {
			if (S.size() == 0) S.push(str[i]);
			else {
				char p = S.top();
				if (p == str[i]) {
					S.pop();
				}
				else S.push(str[i]);	
			}
		}
		// ��� ������ ���� �� stack�� ũ�Ⱑ 0�̸� ��ġ�� ��ġ�� �ʴ� ���̹Ƿ� ����� ++;
		if (S.size() == 0) result++;
		// �ʱ�ȭ
		else {
			while (!S.empty()) S.pop();		
		}
	}
	printf("%d\n", result);

	return 0;
}