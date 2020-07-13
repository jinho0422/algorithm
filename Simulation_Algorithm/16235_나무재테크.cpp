#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K;
int a, b, c;
int board[11][11];
int tmp_board[11][11];
int dirY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dirX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int result;
bool flag;

deque<int> Q[11][11];

void solve();

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			board[hang][yal] = 5;
			scanf("%d", &tmp_board[hang][yal]);
		}
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a][b].push_front(c);
	}

	for (int t = 1; t <= K; t++) {
		solve();
	}

	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			if (Q[hang][yal].size() != 0) {
				result += Q[hang][yal].size();
			}
		}
	}
	printf("%d\n", result);
	return 0;
}

void solve() {
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			int sz = Q[hang][yal].size();
			
			if (sz != 0) {
				flag = false;
				for (int s = 0; s < sz; s++) {
					int p = Q[hang][yal].front();
					Q[hang][yal].pop_front();

					if (board[hang][yal] >= p && !flag) {
						board[hang][yal] -= p;
						Q[hang][yal].push_back(p + 1);
					}
					else {
						flag = true;
						board[hang][yal] += p / 2;
					}
				}
			}
		}
	}

	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			board[hang][yal] += tmp_board[hang][yal];

			int sz = Q[hang][yal].size();

			if (sz != 0) {
				for (int s = 0; s < sz; s++) {
					int p = Q[hang][yal].front();
					Q[hang][yal].pop_front();

					if (p % 5 != 0) {
						Q[hang][yal].push_back(p);
					}
					else {
						Q[hang][yal].push_back(p);
						for (int dir = 0; dir < 8; dir++) {
							int newY = hang + dirY[dir];
							int newX = yal + dirX[dir];

							if (newY < 1 || newY > N || newX < 1 || newX > N) continue;
							Q[newY][newX].push_front(1);
						}
					}
				}
			}
		}
	}
}