/*
	https://www.acmicpc.net/problem/2696
	priority_queue의 오른차순과 내림차순을 통해 중앙값을 뽑아내는 알고리즘 구현..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int N;


priority_queue<int, vector<int>, less<int>>  max_Q; // 내림차순 priority_queue ex> 5,4,3,2,1
priority_queue<int, vector<int>, greater<int>> min_Q; // 오름차순 priority_queue ex> 1,2,3,4,5

vector<int> Vec; // 결과값을 저장하기 위한 vector

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int a, i = 1; i <= N; i++) {
			scanf("%d", &a);
			if (max_Q.size() == min_Q.size()) max_Q.push(a); // 내림차순 PQ와 오름차순 PQ의 크기가 같으면 내림차순 PQ에 넣어주고
			else min_Q.push(a); // 다르면 오름차순 PQ에 넣어준다.

			if (!max_Q.empty() && !min_Q.empty() && (max_Q.top() > min_Q.top())){ // 만약 내림차순의 PQ의 top이 오름차순의 PQ의 top보다 크면
				int p = max_Q.top(); max_Q.pop(); // 서로의 위치를 바꿔준다.. (중앙값은 항상 max_Q의 top이다..)
				int q = min_Q.top(); min_Q.pop();
				min_Q.push(p);
				max_Q.push(q);		
			}
			if (i % 2 != 0) Vec.push_back(max_Q.top()); // 홀수번째일 때 중앙값을 결과값 Vector에 넣어준다..
		}

		int sz = Vec.size();
		int cnt = 0;
		printf("%d\n", sz);
		for (int s = 0; s < sz; s++) {
			printf("%d ", Vec[s]);
			cnt++;
			if (cnt == 10) { // 출력값이 10개가 넘으면 줄을 바꿔주기위해..
				cnt = 0;
				printf("\n");
			}
		}
		printf("\n");
		//초기화 과정..
		while (!max_Q.empty()) max_Q.pop();
		while (!min_Q.empty()) min_Q.pop();
		Vec.clear();
	}
	return 0;
}