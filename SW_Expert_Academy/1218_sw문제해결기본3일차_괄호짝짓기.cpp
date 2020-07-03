#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

char str[10001];
int N;
bool resultFlag;

stack<char> S;

bool equals(char first, char second);

int main() {
	//freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		//입력, 결과값 반영을 위한 resultFlag 초기화
		resultFlag = false;
		scanf("%d", &N);
		scanf("%s", str);

		//문자열의 길이만큼 반복문을 돌리면서 (, [, {, < 나오면 스택에 넣고 ), ], }, > 나오면 가장 난중에 들어온 괄호와 비교하여 짝이 맞는지 판단.
		for (int s = 0; str[s] !='\0'; s++) {
			//printf("%c ", str[s]);
			if (str[s] == '(' || str[s] == '[' || str[s] == '{' || str[s] == '<') {
				S.push(str[s]);
			}
			else {
				char p = S.top();
				bool flag = equals(p, str[s]);
				if (flag) {
					S.pop();
				}
				else {
					resultFlag = true;
					break;
				}
			}
		}
		// 다음 테스트케이스를 위해 stack 초기화..
		while (!S.empty()) S.pop();
		if (resultFlag) printf("#%d 0\n", t);
		else printf("#%d 1\n", t);
	}

	return 0;
}

//괄호의 짝이 맞는지 판단하는 함수..
bool equals(char first, char second) {
	if (first == '(') {
		if (second == ')') return true;
	}
	if (first == '[') {
		if (second == ']') return true;
	}
	if (first == '{') {
		if (second == '}') return true;
	}
	if (first == '<') {
		if (second == '>') return true;
	}
	return false;
}