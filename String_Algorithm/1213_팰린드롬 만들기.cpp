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
	// 이름의 길이가 짝수인 경우
	if (cnt % 2 == 0) {
		for (int s = 0; s <= 25; s++) {
			//짝수인경우 알파벳의 갯수가 홀수이면 만들 수 없다.
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
	// 이름의 길이가 홀수인 경우
	else {
		int odd = 0;
		//이름의 길이가 홀수 인경우 odd가 1이여야 만들 수 있다.
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