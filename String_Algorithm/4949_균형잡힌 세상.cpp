#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string s = "";
stack<char> check;

int main() {
	// 만약 문장이 "."이면 break..
	while(1) {
		bool flag = false; // 괄호가 균형이 잡힌지 판단하는 flag
		getline(cin, s); // string을 띄어쓰기와 공백을 포함해서 받을 수 있다..
		if (s[0] == '.') break;
		// 문장을 보여 괄호 '(','[' 이면 stack에 넣고 ')', ']'이면 stack의 크기가 0이 아니면 비교를 해서 괄호가 균형잡힌지 판단..
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
		// 만약 stack의 크기가 0이 아니면 균형잡히지 않은 것이 있으므로 flag == true;
		if (check.size() != 0) flag = true;
		//출력
		if (flag) printf("no\n");
		else printf("yes\n");
		//초기화
		while (!check.empty()) check.pop();
	
	}
	return 0;
}