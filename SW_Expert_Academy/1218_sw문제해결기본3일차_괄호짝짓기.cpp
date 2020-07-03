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
		//�Է�, ����� �ݿ��� ���� resultFlag �ʱ�ȭ
		resultFlag = false;
		scanf("%d", &N);
		scanf("%s", str);

		//���ڿ��� ���̸�ŭ �ݺ����� �����鼭 (, [, {, < ������ ���ÿ� �ְ� ), ], }, > ������ ���� ���߿� ���� ��ȣ�� ���Ͽ� ¦�� �´��� �Ǵ�.
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
		// ���� �׽�Ʈ���̽��� ���� stack �ʱ�ȭ..
		while (!S.empty()) S.pop();
		if (resultFlag) printf("#%d 0\n", t);
		else printf("#%d 1\n", t);
	}

	return 0;
}

//��ȣ�� ¦�� �´��� �Ǵ��ϴ� �Լ�..
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