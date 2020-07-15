#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> Q;

int main() {
	//입력
	scanf("%d", &N);
	for (int in, s = 0; s < N; s++) {
		scanf("%d", &in);
		//만약 입력값이 0일 때
		if (in == 0) {
			// priority_queue의 size가 0 이면 0을 출력하고 아니면 top()의 값을 출력하고 pop()한다.
			if (Q.size() == 0) printf("0\n");
			else {
				int first = Q.top();
				Q.pop();
				printf("%d\n", first);
			}
		}
		// 입력값이 0이 아니면 priority_queue에 입력값을 push한다.
		else {
			Q.push(in);
		}
	}
	return 0;
}