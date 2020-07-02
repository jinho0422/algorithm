#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int board[101];

int main() {
	//freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		for (int i = 0; i < 100; i++) {
			scanf("%d", &board[i]);
		}
		while(1) {
			sort(board, board + 100);
			board[0]++;
			board[99]--;
			N--;
			if (N == 0) break;
		}
		sort(board, board + 100);
		printf("#%d %d\n", t, board[99] - board[0]);
	}

	return 0;
}