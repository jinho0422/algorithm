#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N;
int board[9];
int tmp[9];
bool check[9];
int max_result;

void solve_DFS(int depth);

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	solve_DFS(0);
	printf("%d\n", max_result);
	return 0;
}

void solve_DFS(int depth) {
	if (depth == N) {
		int sum = 0;
		for (int i = 0; i < N - 1; i++) {
			sum += abs(tmp[i] - tmp[i + 1]);
		}
		if (max_result < sum) max_result = sum;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = board[i];
			solve_DFS(depth + 1);
			tmp[depth] = 0;
			check[i] = false;
		}
	}
}