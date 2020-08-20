#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

char str[51];
int board[27];
char oddName;

deque<char> Q;

int main() {
	scanf("%s", str);
	int cnt = 0;
	for (int s = 0; str[s] != '\0'; s++) {
		board[str[s] - 'A']++;
		cnt++;
	}
	bool flag = false;
	// �̸��� ���̰� ¦���� ���
	if (cnt % 2 == 0) {
		for (int s = 0; s <= 25; s++) {
			//¦���ΰ�� ���ĺ��� ������ Ȧ���̸� ���� �� ����.
			if (board[s] % 2 != 0) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			for (int s = 25; s >= 0; s--) {
				int sz = board[s];
				for (int i = 0; i < sz / 2; i++) {
					Q.push_back(s + 'A');
					Q.push_front(s + 'A');
				}
			}
			while (!Q.empty()) {
				printf("%c", Q.front());
				Q.pop_front();
			}
			printf("\n");
		}
		else {
			printf("I'm Sorry Hansoo\n");
		}
	}
	// �̸��� ���̰� Ȧ���� ���
	else {
		int odd = 0;
		//�̸��� ���̰� Ȧ�� �ΰ�� odd�� 1�̿��� ���� �� �ִ�.
		for (int s = 0; s <= 25; s++) {
			if (board[s] % 2 != 0) {
				odd++;
				oddName = s + 'A';
				board[s]--;
			}
		}
		if (odd == 1) {
			Q.push_back(oddName);
			for (int s = 25; s >= 0; s--) {
				int sz = board[s];
				for (int i = 0; i < sz / 2; i++) {
					Q.push_back(s + 'A');
					Q.push_front(s + 'A');
				}
			}
			while (!Q.empty()) {
				printf("%c", Q.front());
				Q.pop_front();
			}
			printf("\n");
		}
		else {
			printf("I'm Sorry Hansoo\n");
		}
	}
	return 0;
}