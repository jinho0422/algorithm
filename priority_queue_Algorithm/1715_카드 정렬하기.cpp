/*
	https://www.acmicpc.net/problem/1715
	카드묶음이 2개이상있을 때는 항상 작은 2개를 섞어서 놔두어야 
	최소한의 비교를 할 수 있다. 그러기때문에 priority_queue를 사용하여
	항상 작은 값이 먼저 나올 수 있게하는 알고리즘을 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>


using namespace std;

int N;
int result;

priority_queue<int, vector<int>, greater<int>> Q; // 작은 수부터 나올 수 있는 priority_queue

int main() {
	scanf("%d", &N);
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		Q.push(a);
	}

	if (Q.size() == 1) { // 만약 카드묶음이 1개이면 비교를 하지 않아도 되므로..
		printf("0\n");
		return 0;
	}

	while (!Q.empty()) { // 카드묶음이 2개 이상이라면..
		if (Q.size() >= 2) {
			int p = Q.top();
			Q.pop();
			int q = Q.top();
			Q.pop(); // 2개의 카드를 꺼내서 
			result += (p + q); // 결과값에 ++
			if (Q.size() != 0) Q.push(p + q); // 꺼낸 두개의 값을 더해서 queue에 다시 넣는다.
			else break;
		}
	}
	printf("%d\n", result);
	return 0;
}