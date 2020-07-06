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
	//입력과 str의 길이를 알기위해서..
	scanf("%s", str);
	while (str[len] != '\0') len++;
	solve(len);
	return 0;
}

void solve(int length) {
	int cnt= 0;
	//str 길이만큼 보면서
	while (cnt < length) {
		// '( )' 의 depth?를 나눠주기위해서 '('가 나타나면 stack에 -1을 넣어준다.
		if (str[cnt] == '(') S.push(-1);


		// ')' 을 만나게 되면 stack에서 -1( '(' )이 나타날 때까지 안의 값을 quantity값에 더해주면서 괄호 안을 계산한다.
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
		// 숫자가 나타나면 바로 앞의 화학실량에 숫자(2~ 9) 값을 곱해서 stack에 넣어준다..
		else if (str[cnt] >= '2' && str[cnt] <= '9') {
			int p = S.top();
			if (p != -1) {
				S.pop(); S.push(p * (str[cnt] - '0'));
			}
		}
		// H, C, O을 만나면 각각의 화학식량을 넣어준다.
		else if (str[cnt] == 'H') S.push(1);
		else if (str[cnt] == 'C') S.push(12);
		else if (str[cnt] == 'O') S.push(16);
		cnt++;
	}
	// 화학식 길이를 모두 본 후에는 stack에는 각 괄호를 처리한 화학식량이 들어가 있기때문에 전부 더해준다.
	while (!S.empty()) {
		result += S.top();
		S.pop();
	}
	printf("%d\n", result);
}