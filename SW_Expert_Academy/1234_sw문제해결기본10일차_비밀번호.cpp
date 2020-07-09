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
	//입력 문자의 갯수와 문자열 받기.
	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		scanf("%s", str);

		//문자열의 길이만큼 돌면서
		for (int s = 0; s < N; s++) {
			int sz = S.size();
			// stack이 비어있으면 문자를 넣어주고 
			if (sz == 0) S.push(str[s] - '0');

			//아니라면 스택의 top을 보고 str[s]와 같으면 top을 빼주고 아니면 str[s]를 넣어준다.
			else {
				int frontCh = S.top();
				if (frontCh == str[s] - '0') {
					S.pop();
				}
				else S.push(str[s] - '0');
			}
		}
		//출력
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