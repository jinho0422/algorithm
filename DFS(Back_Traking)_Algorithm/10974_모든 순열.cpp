#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N;
int tmp[9];
bool check[9];

void solve_DFS(int dpeth);

int main() {
	scanf("%d", &N);
	solve_DFS(0);
	return 0;
}

void solve_DFS(int depth) {
	if (depth == N) {
		for (int i = 0; i < N; i++) {
			printf("%d ", tmp[i]);
		}
		printf("\n");
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = i;
			solve_DFS(depth + 1);
			tmp[depth] = 0;
			check[i] = false;
		}
	}
}