#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int board[9];
int result[8];
bool flag;

void DFS(int depth, int start, int sum);

int main() {
	//입력
	for (int i = 0; i < 9; i++) {
		scanf("%d", &board[i]);
	}
	// 오름차순으로 조합을 만들기 위해..
	sort(board, board + 9);
	// 7명의 난쟁이의 키를 합하기 위한 DFS
	DFS(0, 0, 0);

	return 0;
}

void DFS(int depth, int start, int sum) {
	// 난쟁이의 키가100이면 다음부터는 무시, sum 100보다 크면 return, 난쟁이가 7명이 넘어가면 return
	if (flag) return;
	if (sum > 100) return;
	if (depth > 7) return;
	if (depth == 7 && sum == 100) {
		flag = true;
		for (int i = 0; i < 7; i++) {
			printf("%d\n", result[i]);
		}
		return;
	}
	// 9명의 난쟁이 중에 7명을 조합으로 뽑기.
	for (int s = start; s < 9; s++) {
		sum += board[s];
		result[depth] = board[s];
		DFS(depth + 1, s + 1, sum);
		sum -= board[s];
	}
}