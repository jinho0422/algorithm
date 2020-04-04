/*
	https://www.acmicpc.net/problem/10971
	 DFS�� Ȱ���� ���� ���Ʈ ����Ȱ���Ͽ� �˰��� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
int board[11][11]; // hang���� yal�� �湮�� �� ��� ���..
bool check[11]; // �湮�� �������� üũ�ϱ� ���� �迭..
int tmp[11]; // ������ �ֱ� ���� �迭..
int min_result; // �ּ� �����..

void solve_DFS(int depth);

int main() {
	min_result = 2147000000; 
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);	
		}
	}
	solve_DFS(0); // depth(����)�� 0���� �Ͽ� DFS
	printf("%d\n", min_result);

	return 0;
}

void solve_DFS(int depth) {
	if (depth == N) { // �湮�� ���� ������ ��������..
		int sum = 0;
		for (int i = 0; i < N -1; i++) { // �湮�� ���� ������� ����ִ� tmp����
			if (board[tmp[i]][tmp[i + 1]] == 0) return; // ���� 0�̸� �湮�� �� ���� ���̹Ƿ�
			sum += board[tmp[i]][tmp[i + 1]]; // �湮�� �� �մ� ���̸� sum �� �����ش�.
		}

		if (board[tmp[N - 1]][tmp[0]] == 0) return; // ���������� �湮�� �� ���� ���̸� return..
		sum += board[tmp[N - 1]][tmp[0]]; // ������ �湮�ϰ� �ǵ��� �� �� ������ sum �� �����ش�.
		if (min_result > sum) min_result = sum;	// ��� ���� �湮�ϰ� ���ƿ��� �� �ּҺ�밪 ����..
		return;
	}

	for (int i = 0; i < N; i++) { // �湮�� ��� ���� ������ ������ ���ϴ�..
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = i;
			solve_DFS(depth + 1);
			tmp[depth] = 0;
			check[i] = false;
		}
	}
}