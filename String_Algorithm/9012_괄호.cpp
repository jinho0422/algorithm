#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

int T;
char s[54];
stack<char> check;

int main() {
	//�Է�
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf(" %s", s);
		bool flag = false;
		//�ѹ����� ���鼭 '(' �̸� stack�� �ְ� ')'�̸� stack�� ũ�Ⱑ 0�� �ƴϸ� stack.top�� ���ؼ� ó��..
		for (int j = 0; s[j] != '\0'; j++) {
			if (s[j] == '(') check.push(s[j]);
			else if (s[j] == ')') {
				if (check.size() == 0) {
					flag = true;
					break;
				}
				char p = check.top();
				if ( p == '(') {
					check.pop();
				}
				else {
					flag = true;
					break;
				}
			}
		}
		// ���� stack�� size�� 0�� �ƴϸ� ��ȣ�� �ȸ��������� �ֱ� ������ flag == true;
		if (check.size() != 0) flag = true;
		//���
		if (flag) printf("NO\n");
		else printf("YES\n");
		//�ʱ�ȭ
		while (!check.empty()) check.pop();
	}
	return 0;
}