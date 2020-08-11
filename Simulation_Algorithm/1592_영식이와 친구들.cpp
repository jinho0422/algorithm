#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


int N, M, L;
int board[1001];

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &L);
	//첫번째 사람이 받는 값
	board[1] = 1;
	//볼이 움직임을 보여주는 변수
	int ball = 1;
	// 결과값
	int cnt = 0;
	while (1) {
		cnt++;
		// 짝수일때는 L만큼 움직이고 원으로 앉아 있으므로 ball의 값이 0이 되면 사람의 수를 더해준다.
		if (board[ball] / 2 == 0) {
			ball -= L;
			if (ball <= 0) ball += N;
			board[ball]++;
			if (board[ball] == M) break;
		}
		//홀수일때는 L만큼 시계방향으로 움직이고 사람의 수보다 ball이 커지면 사람의 수만큼 빼준다.
		else {
			ball += L;
			if (ball > N) ball -= N;
			board[ball]++;
			if (board[ball] == M) break;
		}
	}
	printf("%d\n", cnt);
	return 0;
}