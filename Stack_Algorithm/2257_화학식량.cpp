#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

char str[105];
int result;
int len;
stack<int> S;

void solve(int length);

int main() {
	//�Է°� str�� ���̸� �˱����ؼ�..
	scanf("%s", str);
	while (str[len] != '\0') len++;
	solve(len);
	return 0;
}

void solve(int length) {
	int cnt= 0;
	//str ���̸�ŭ ���鼭
	while (cnt < length) {
		// '( )' �� depth?�� �����ֱ����ؼ� '('�� ��Ÿ���� stack�� -1�� �־��ش�.
		if (str[cnt] == '(') S.push(-1);


		// ')' �� ������ �Ǹ� stack���� -1( '(' )�� ��Ÿ�� ������ ���� ���� quantity���� �����ָ鼭 ��ȣ ���� ����Ѵ�.
		else if (str[cnt] == ')') {
			int quantity = 0;
			while (1) {
				int p = S.top();
				if (p == -1) {
					S.pop(); S.push(quantity);
					break;
				}
				else {
					quantity += p; S.pop();
				}
			}
		}
		// ���ڰ� ��Ÿ���� �ٷ� ���� ȭ�нǷ��� ����(2~ 9) ���� ���ؼ� stack�� �־��ش�..
		else if (str[cnt] >= '2' && str[cnt] <= '9') {
			int p = S.top();
			if (p != -1) {
				S.pop(); S.push(p * (str[cnt] - '0'));
			}
		}
		// H, C, O�� ������ ������ ȭ�нķ��� �־��ش�.
		else if (str[cnt] == 'H') S.push(1);
		else if (str[cnt] == 'C') S.push(12);
		else if (str[cnt] == 'O') S.push(16);
		cnt++;
	}
	// ȭ�н� ���̸� ��� �� �Ŀ��� stack���� �� ��ȣ�� ó���� ȭ�нķ��� �� �ֱ⶧���� ���� �����ش�.
	while (!S.empty()) {
		result += S.top();
		S.pop();
	}
	printf("%d\n", result);
}