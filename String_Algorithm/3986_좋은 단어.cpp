#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>

using namespace std;

int N;
char str[100001];
int result;
stack<char> S; // stack을 사용한 이유는 아치형이 겹치는 것을 판단하기 위해..

int main() {
	//입력
	scanf("%d", &N);
	for (int s = 0; s < N; s++) {
		scanf("%s", str);
		// stack의 size가 0 이면 str[i]를 넣어주고 0이 아니면 다음 단어와 비교하면서 같으면 pop 아니면 push를 해준다.
		for (int i = 0; str[i] !='\0'; i++) {
			if (S.size() == 0) S.push(str[i]);
			else {
				char p = S.top();
				if (p == str[i]) {
					S.pop();
				}
				else S.push(str[i]);	
			}
		}
		// 모든 문장을 봤을 때 stack의 크기가 0이면 아치가 곂치지 않는 것이므로 결과값 ++;
		if (S.size() == 0) result++;
		// 초기화
		else {
			while (!S.empty()) S.pop();		
		}
	}
	printf("%d\n", result);

	return 0;
}