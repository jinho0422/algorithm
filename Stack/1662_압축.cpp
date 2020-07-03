#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

char str[55];
stack<int> S;
int resultLength;

int main() {
	//입력!
	scanf("%s", str);
	//입력된 문자를 앞에서부터보며
	for (int s = 0; str[s] != '\0'; s++) {
		// '(' 일 때 -1 을 stack값에 넣고 0~9일때는 int 형으로 0~9를 넣는다.
		if (str[s] == '(') S.push(-1);	
		else if (str[s] >= '0' && str[s] <= '9') {
			S.push(str[s] - '0');
		}
		// ')' 만났을 때는 
		else if (str[s] == ')') {
			int cnt = 0;
			while (1) {
				// -1은 '('을 나타내므로 빠져나온다.
				if (S.top() == -1) {
					S.pop();
					break;
				}
				// 만일 stack의 top값이 0~9이면 한번도 나오지 않은 문자열 숫자이므로 cnt++,
				// 10이상이면 연산을 통해 그 길이에  +10을 해서 넣은 것이므로 -10을 해서 길이에 넣어준다.
				if (S.top() <= 9 && S.top() >= 0) cnt++;
				else cnt += S.top() - 10;
				S.pop();
			}
			//따라서 ()안에있는 숫자의 길이는 cnt이고 그 다음 stack의 top은 길이에 곱하기를 할 값이므로 곱해주고 연산이 한번 정의된 것이므로 +10을 해서 넣어준다.
			cnt = S.top() * cnt;
			S.pop();
			S.push(cnt + 10);
		}
	}
	// 스택의 모든 연산이 정리된 값이므로 스택을 빼내면서 결과값을 생성해준다.
	while (!S.empty()) {
		if (S.top() >= 10) resultLength += S.top() - 10;
		else resultLength++;
		S.pop();
	}

	printf("%d\n", resultLength);
	return 0;
}

