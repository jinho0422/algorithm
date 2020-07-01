#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int board[1001];
int result_view;

int main() {
	freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		result_view = 0;
		scanf("%d", &N);
		for (int height, i = 0; i < N; i++) {
			scanf("%d", &height);
			board[i] = height;
		}
		for (int i = 2; i < N - 2; i++) {
			int max_view = 256;
			bool flag = false;
			for (int j = i - 2; j <= i + 2; j++) {
				if (i == j) continue;
				if (board[i] > board[j]) {
					int view = board[i] - board[j];
					if (max_view > view) max_view = view;
				}
				else {
					flag = true;
					break;
				}
			}
			if (!flag) {
				result_view += max_view;
			}
		}
		printf("#%d %d\n", t, result_view);
	}

	return 0;
}