/*
	https://www.acmicpc.net/problem/10971
	 DFS를 활용한 순열 브루트 포스활용하여 알고리즘 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
int board[11][11]; // hang에서 yal로 방문할 때 드는 비용..
bool check[11]; // 방문한 곳인지를 체크하기 위한 배열..
int tmp[11]; // 순열을 넣기 위한 배열..
int min_result; // 최소 결과값..

void solve_DFS(int depth);

int main() {
	min_result = 2147000000; 
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);	
		}
	}
	solve_DFS(0); // depth(깊이)를 0으로 하여 DFS
	printf("%d\n", min_result);

	return 0;
}

void solve_DFS(int depth) {
	if (depth == N) { // 방문할 곳의 순서가 정해지면..
		int sum = 0;
		for (int i = 0; i < N -1; i++) { // 방문할 곳이 순서대로 들어있는 tmp에서
			if (board[tmp[i]][tmp[i + 1]] == 0) return; // 만약 0이면 방문할 수 없는 곳이므로
			sum += board[tmp[i]][tmp[i + 1]]; // 방문할 수 잇는 곳이면 sum 에 더해준다.
		}

		if (board[tmp[N - 1]][tmp[0]] == 0) return; // 마지막에서 방문할 수 없는 곳이면 return..
		sum += board[tmp[N - 1]][tmp[0]]; // 모든곳을 방문하고 되돌아 올 수 있으면 sum 에 더해준다.
		if (min_result > sum) min_result = sum;	// 모든 곳을 방문하고 돌아왔을 때 최소비용값 갱신..
		return;
	}

	for (int i = 0; i < N; i++) { // 방문할 모든 곳의 순서를 순열로 구하는..
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = i;
			solve_DFS(depth + 1);
			tmp[depth] = 0;
			check[i] = false;
		}
	}
}