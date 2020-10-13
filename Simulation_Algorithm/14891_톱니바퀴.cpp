#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

int K;
char str[9];
bool check[6]; // 각 톱니바퀴가 움직일 수 있는 여부
int turns[6]; // 각 톱니바퀴가움직일 수 있으면 어느방향으로 돌지..
int result;

deque<int> Q[6];

void checkMove(int start, int turn) {
	memset(check, false, sizeof(check));
	check[start] = true;
	turns[start] = turn;
	if (start == 1) {
		if (Q[start][2] != Q[start + 1][6]) {
			check[start + 1] = true;
			turns[start + 1] = turn * -1;
			if (Q[start + 1][2] != Q[start + 2][6]) {
				check[start + 2] = true;
				turns[start + 2] = turn;
				if (Q[start + 2][2] != Q[start + 3][6]) {
					check[start + 3] = true;
					turns[start + 3] = turn * -1;
				}
			}
		}
	}
	else if (start == 2) {
		if (Q[start][6] != Q[start - 1][2]) {
			check[start - 1] = true;
			turns[start - 1] = turn * -1;
		}
		if (Q[start][2] != Q[start + 1][6]) {
			check[start + 1] = true;
			turns[start + 1] = turn * -1;
			if (Q[start + 1][2] != Q[start + 2][6]) {
				check[start + 2] = true;
				turns[start + 2] = turn;
			}
		}
	}
	else if (start == 3) {
		if (Q[start][2] != Q[start + 1][6]) {
			check[start + 1] = true;
			turns[start + 1] = turn * -1;
		}
		if (Q[start][6] != Q[start - 1][2]) {
			check[start - 1] = true;
			turns[start - 1] = turn * -1;
			if (Q[start - 1][6] != Q[start - 2][2]) {
				check[start - 2] = true;
				turns[start - 2] = turn;
			}
		}
	}
	else {
		if (Q[start][6] != Q[start - 1][2]) {
			check[start - 1] = true;
			turns[start - 1] = turn * -1;
			if (Q[start - 1][6] != Q[start - 2][2]) {
				check[start - 2] = true;
				turns[start - 2] = turn;
				if (Q[start - 2][6] != Q[start - 3][2]) {
					check[start - 3] = true;
					turns[start - 3] = turn * -1;
				}
			}
		}
	}
}

void move(int i, int turns) {
	if (turns == 1) {
		if (!check[i]) return;
		int p = Q[i].back();
		Q[i].pop_back();
		Q[i].push_front(p);
	}
	else {
		if (!check[i]) return;
		int p = Q[i].front();
		Q[i].pop_front();
		Q[i].push_back(p);
	}
}

int main() {
	for (int hang = 1; hang <= 4; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < 8; yal++) {
			Q[hang].push_back(str[yal] - '0');
		}
	}
	scanf("%d", &K);
	for (int a, b, i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		checkMove(a, b); // 각 톱니바퀴가 움직일 수 있는 여부와 움직이는 뱡향을 찾는 함수
		for (int j = 1; j <= 4; j++) move(j,turns[j]); // 움직일 수 있는 톱니바퀴 움직이기
	}
	// 결과값 갱신 및 출력
	for (int i = 1; i <= 4; i++) if (Q[i][0] == 1) result += pow(2, i - 1);
	printf("%d\n", result);
	return 0;
}