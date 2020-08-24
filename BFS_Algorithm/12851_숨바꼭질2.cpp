#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
bool check[100002];
int result, cnt;


queue<int> Q;

void BFS(int start);

int main() {
	//입력
	scanf("%d %d", &N, &K);
	BFS(N);
	//출력
	printf("%d\n%d\n", result, cnt); // result : 시간 결과값, cnt ; 그 시간에 몇번을도착하는지
	return 0;
}

void BFS(int start) {
	bool bkFlag = false; // 만약 그 시간에 동생을 찾았다면 bkFlag = true;
	Q.push(start);
	while (!Q.empty()) {
		int sz = Q.size(); // 시간당으로 보기 위해.. Q의 size만큼 돌린다..
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			if (p == K) { // 만약 동생을 만났다면
				cnt++; // 카운트를 세고 
				bkFlag = true; // 빠져나갈 bkFlag = true로 한다..
				continue;
			}
			check[p] = true;
			if (p + 1 <= 100000) { // 앞으로 한칸 전진
				if (!check[p + 1]) {
					Q.push(p + 1);
				}
			}
			if (p - 1 >= 0) { //뒤로 한칸 후진
				if (!check[p - 1]) {
					Q.push(p - 1);
				}
			}
			if (p * 2 <= 100000) { // 순간이동..
				if (!check[p * 2]) {
					Q.push(p * 2);
				}
			}
		}
		if (bkFlag) break;
		result++;	
	}
}