#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

char str[55];
stack<int> S;
int resultLength;

int main() {
	//�Է�!
	scanf("%s", str);
	//�Էµ� ���ڸ� �տ������ͺ���
	for (int s = 0; str[s] != '\0'; s++) {
		// '(' �� �� -1 �� stack���� �ְ� 0~9�϶��� int ������ 0~9�� �ִ´�.
		if (str[s] == '(') S.push(-1);	
		else if (str[s] >= '0' && str[s] <= '9') {
			S.push(str[s] - '0');
		}
		// ')' ������ ���� 
		else if (str[s] == ')') {
			int cnt = 0;
			while (1) {
				// -1�� '('�� ��Ÿ���Ƿ� �������´�.
				if (S.top() == -1) {
					S.pop();
					break;
				}
				// ���� stack�� top���� 0~9�̸� �ѹ��� ������ ���� ���ڿ� �����̹Ƿ� cnt++,
				// 10�̻��̸� ������ ���� �� ���̿�  +10�� �ؼ� ���� ���̹Ƿ� -10�� �ؼ� ���̿� �־��ش�.
				if (S.top() <= 9 && S.top() >= 0) cnt++;
				else cnt += S.top() - 10;
				S.pop();
			}
			//���� ()�ȿ��ִ� ������ ���̴� cnt�̰� �� ���� stack�� top�� ���̿� ���ϱ⸦ �� ���̹Ƿ� �����ְ� ������ �ѹ� ���ǵ� ���̹Ƿ� +10�� �ؼ� �־��ش�.
			cnt = S.top() * cnt;
			S.pop();
			S.push(cnt + 10);
		}
	}
	// ������ ��� ������ ������ ���̹Ƿ� ������ �����鼭 ������� �������ش�.
	while (!S.empty()) {
		if (S.top() >= 10) resultLength += S.top() - 10;
		else resultLength++;
		S.pop();
	}

	printf("%d\n", resultLength);
	return 0;
}

