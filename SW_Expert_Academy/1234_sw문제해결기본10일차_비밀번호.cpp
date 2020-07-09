#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
using namespace std;

int N;
char str[102];
int board[102];

stack<int> S;

int main() {
	//freopen("test.txt", "r", stdin);
	//�Է� ������ ������ ���ڿ� �ޱ�.
	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		scanf("%s", str);

		//���ڿ��� ���̸�ŭ ���鼭
		for (int s = 0; s < N; s++) {
			int sz = S.size();
			// stack�� ��������� ���ڸ� �־��ְ� 
			if (sz == 0) S.push(str[s] - '0');

			//�ƴ϶�� ������ top�� ���� str[s]�� ������ top�� ���ְ� �ƴϸ� str[s]�� �־��ش�.
			else {
				int frontCh = S.top();
				if (frontCh == str[s] - '0') {
					S.pop();
				}
				else S.push(str[s] - '0');
			}
		}
		//���
		printf("#%d ", t);
		int num = 0;
		while (!S.empty()) {
			board[num++] = S.top();
			S.pop();
		}
		for (int s = num -1; s >=0 ; s--) {
			printf("%d", board[s]);
		}
		printf("\n");
	}
	return 0;
}