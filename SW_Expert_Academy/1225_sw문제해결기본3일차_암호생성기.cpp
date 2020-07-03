#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

bool flag;
// front에서 해결한 값을 back으로 넣어야 하기 때문에 deque 사용 
deque<int> Q;

int main() {
	//freopen("test.txt", "r", stdin);
	int T;
	for (int t = 1; t <= 10; t++) {
		//입력값 deque에 넣어준다.
		scanf("%d", &T);
		flag = false;
		for (int numbers, i = 0; i < 8; i++) {
			scanf("%d", &numbers);
			Q.push_back(numbers);
		}
		// 반복적인 계산(한 사이클 (1~5)를 빼면서)을 하면서 만약 계산결과가 0이하이면 사이클을 멈춘다.
		while(!flag) {
			for (int i = 1; i <= 5; i++) {
				int p = Q.front();
				Q.pop_front();
				if (p - i <= 0) {
					flag = true;
					Q.push_back(0);
					break;
				}
				else {
					Q.push_back(p - i);
				}
			}
		}
		//출력부분
		printf("#%d ", t);
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop_front();
			printf("%d ", p);
		}
		printf("\n");
	}
	return 0;
}