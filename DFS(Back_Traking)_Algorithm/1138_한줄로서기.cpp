#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int board[11];
bool check[11];
int tmp[11];
bool flag;

void DFS(int depth);

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &board[i]);
	}
	DFS(0);

	return 0;
}

void DFS(int depth) {
	if (flag) return;

	if (depth == N) {
		int resultCnt = 0;
		for (int i = 1; i <= depth; i++) {
			int cnt = 0;
			for (int j = 0; j < depth; j++) {
				if (tmp[j] == i) {
					if (board[i] == cnt) resultCnt++;
					break;
				}
				if (tmp[j] > i) cnt++;
			}
			if (resultCnt != i) break;
		}
		if (resultCnt == N) {
			flag = true;
			for (int i = 0; i < depth; i++) {
				printf("%d ", tmp[i]);
			}
			printf("\n");
		}

		return;
	}
	for (int i = 1; i <= N; i++) {
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = i;
			DFS(depth + 1);
			check[i] = false;
			tmp[depth] = 0;
		}
	}
}