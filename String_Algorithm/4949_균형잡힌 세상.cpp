#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string s = "";
stack<char> check;

int main() {
	// ���� ������ "."�̸� break..
	while(1) {
		bool flag = false; // ��ȣ�� ������ ������ �Ǵ��ϴ� flag
		getline(cin, s); // string�� ����� ������ �����ؼ� ���� �� �ִ�..
		if (s[0] == '.') break;
		// ������ ���� ��ȣ '(','[' �̸� stack�� �ְ� ')', ']'�̸� stack�� ũ�Ⱑ 0�� �ƴϸ� �񱳸� �ؼ� ��ȣ�� ���������� �Ǵ�..
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(' || s[i] == '[') check.push(s[i]);
			else if (s[i] == ')' || s[i] == ']') {
				if (check.size() == 0) {
					flag = true;
					break;
				}
				else {
					char p = check.top();
					if (s[i] == ')' && p == '(' || s[i] == ']' && p == '[') {
						check.pop();
					}
					else {
						flag = true;
						break;
					}
				}
			}
		}
		// ���� stack�� ũ�Ⱑ 0�� �ƴϸ� ���������� ���� ���� �����Ƿ� flag == true;
		if (check.size() != 0) flag = true;
		//���
		if (flag) printf("no\n");
		else printf("yes\n");
		//�ʱ�ȭ
		while (!check.empty()) check.pop();
	
	}
	return 0;
}