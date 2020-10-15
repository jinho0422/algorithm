#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

int N, M, K;
int board[10][10];
bool check[10][10];
int honey[2][5];
int result, r;

deque<int> first;

void solve(int hang, int yal);
void DFS(int depth, int start, int c, int sum, int res);

int main() {
	freopen("test.txt", "r", stdin);
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		result = 0;
		memset(check, false, sizeof(check));
		while (!first.empty()) first.pop_back();
		memset(honey, 0, sizeof(honey));

		scanf("%d %d %d", &N, &M, &K);
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				scanf("%d", &board[hang][yal]);
			}
		}
		for (int i = 0; i < M; i++) {
			check[0][i] = true;
			first.push_back(board[0][i]);
		}
		
		int sh = 0, sy = M - 1;

		while (1) {
			for (int i = 0; i < M; i++) honey[0][i] = first[i];
			r = 0;
			DFS(0, 0, 0, 0, 0);
			int sum = r;
			for (int hang = sh; hang < N; hang++) {
				for (int yal = 0; yal <= N - M; yal++) {
					if (!check[hang][yal]) {
						solve(hang, yal);
						r = 0;
						DFS(0, 0, 1, 0, 0);
						sum += r;
						if (sum == 161) {
							for (int i = 0; i < 2; i++) {
								for (int j = 0; j < M; j++) {
									printf("%d ", honey[i][j]);
								}
								printf("\n");
							}
						}
						if (result < sum) result = sum;
						sum -= r;
					}
				}
			}

			sy++;
			if (sy == N) {
				sh++, sy = M - 1;
				while (!first.empty()) first.pop_front();
				if (sh == N) break;
				for (int i = 0; i < M; i++) {
					check[sh][i] = true;
					first.push_back(board[sh][i]);
				}
			}	
			else {
				check[sh][sy] = true;
				first.pop_front();
				first.push_back(board[sh][sy]);
			}
		}
		printf("#%d %d\n", t, result);
	}
	return 0;
}

void solve(int hang, int yal) {
	int num = 0;
	for (int i = yal; i < yal + M; i++) honey[1][num++] = board[hang][i];
}

void DFS(int depth, int start, int c, int sum, int res) {
	if (sum > K) return;

	if (depth <= M) {
		if (r < res) r = res;
		if (depth == M) return;
	}
	for (int i = start; i < M; i++) {
		DFS(depth + 1, i + 1, c, sum + honey[c][i], res + (honey[c][i]*honey[c][i]));
	}

}