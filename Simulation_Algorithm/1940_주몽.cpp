#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int board[15001];
bool check[10000001];
int result;

int main() {
	//입력
	scanf("%d %d", &N, &M);
	// 재료의 고유번호를 board에 넣어주고 재료가 있는 번호를 check = true해준다..
	for (int a, s = 0; s < N; s++) {
		scanf("%d", &a);
		board[s] = a;
		check[a] = true;
	}
	// 모든 재료를 돌면서
	for (int s = 0; s < N; s++) {
		// 값옷을 만드는데 필요한 번호에서 빼며
		int first = M - board[s];
		// 고유의 번호이므로 현재의 재료와 뺀 값이 같으면 같은 종류이므로 continue.. 뺏을때 작으면 continue(만들수없으므로)
		if (first == board[s] || first <= 0) {
			continue;
		}
		if (check[M - board[s]]) result++;
	}
	// 양쪽을 다 본 경우이므로 결과값에서 /2를 해준다.
	printf("%d\n", result / 2);

	return 0;
}