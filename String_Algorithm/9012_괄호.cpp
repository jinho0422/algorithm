#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

int T;
char s[54];
stack<char> check;

int main() {
	//입력
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf(" %s", s);
		bool flag = false;
		//한문장을 돌면서 '(' 이면 stack에 넣고 ')'이면 stack의 크기가 0이 아니면 stack.top과 비교해서 처리..
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
		// 만약 stack의 size가 0이 아니면 괄호가 안맞춰진것이 있기 때문에 flag == true;
		if (check.size() != 0) flag = true;
		//출력
		if (flag) printf("NO\n");
		else printf("YES\n");
		//초기화
		while (!check.empty()) check.pop();
	}
	return 0;
}