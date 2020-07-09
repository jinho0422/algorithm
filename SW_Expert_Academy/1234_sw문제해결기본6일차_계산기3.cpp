#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

int N;
char str;
int result;

vector<char> Vec;
stack<int> S;

int main() {
	//freopen("test.txt", "r", stdin);
	//입력, 결과값 초기화..
	for (int t = 1; t <= 10; t++) {
		result = 0;
		scanf("%d", &N);
		for (int s = 0; s <= N; s++) {
			scanf("%c", &str);
			Vec.push_back(str);
		}
		int sz = Vec.size();
		// 0 부터 계산식의 길이까지 보면서
		for (int s = 0; s < sz; s++) {
			//'+' continue
			if (Vec[s] == '+') continue;
			//'*' 일 때에는 다음 계산식이 '('이면 곱하기를 뜻하는 -2와 (를 뜻하는 -1를 stack에 넣어준다
			else if (Vec[s] == '*') {
				int first = S.top();
				s++;
				if (Vec[s] == '(') {
					S.push(-2);
					S.push(-1);
				}
				// 숫자이면 stack top에 있는 숫자와 곱해서 넣어준다.
				else {
					S.pop();
					S.push(first * (Vec[s] - '0'));
				}
			}
			else if (Vec[s] == '(') S.push(-1);
			else if (Vec[s] >= '0' && Vec[s] <= '9') S.push(Vec[s] - '0');
			
			// ')'를 만났을 때는 '('를 가르키는 -1이 나올때까지 cnt에 stack의 값을 더해준다..
			else if (Vec[s] == ')') {
				int cnt = 0;
				while (1) {
					int p = S.top();
					//-1을 만났을 때 그 전에 있던 stack의 숫자가 -2이면 그 전전에 있던 수와 곱해서 넣어준다.
					if (p == -1) {
						S.pop();
						if (S.size() != 0) {
							p = S.top();
							if (p == -2) {
								S.pop();
								p = S.top();
								cnt *= p;
								S.pop();
							}
						}
						S.push(cnt);
						break;
					}
					// 만약 -2가 있으면 곱해주고
					else if (p == -2) {
						S.pop();
						int p = S.top();
						S.pop();
						cnt *= p;
					}
					else {
						S.pop();
						cnt += p;
					}
				}
			}
		}
		while (!S.empty()) {
			result += S.top();
			S.pop();
		}
		printf("#%d %d\n", t, result);
		Vec.clear();
	}

	return 0;
}