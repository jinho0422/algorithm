#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, K;
int board[100001];
int maxTemp;

int main() {
	// 각 온도가 -100 ~ 100 까지 이므로 최소로 나올 수 있는 값은 -100 * 100,000 이다.
	maxTemp = -2147000000;
	//입력
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	int sum = 0, cnt = 0; // sum : K개씩 합한 값, cnt : K개가 되는 지점을 파악
	for (int i = 0; i < N; i++) {
		// K개가 되면 K개 전을 빼주고 현재를 더해준다.
		if (cnt == K) {
			// 갱신
			if (maxTemp < sum) maxTemp = sum;
			sum -= board[i - cnt];
			sum += board[i];
			//갱신
			if (maxTemp < sum) maxTemp = sum;
		}
		// K개가 더해지지 않았으면 더해준다
		else {
			sum += board[i];
			cnt++;
		}
	}
	// 갱신
	if (maxTemp < sum) maxTemp = sum;
	printf("%d\n", maxTemp);
	return 0;
}