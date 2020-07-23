#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N;
int number[12];
int tmp[12];
int operators[5];
int max_result;
int min_result;

void solve(int dpeth);

int main() {
	max_result = -1000000002;
	min_result = 1000000002;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &number[i]);
	}
	for (int i = 1; i <= 4; i++) {
		scanf("%d", &operators[i]);
	}

	solve(0);
	printf("%d\n%d\n", max_result, min_result);
	return 0;
}

void solve(int depth) {
	if (depth == N - 1) {
		int sum = number[0];
		for (int i = 0; i < depth; i++) {
			if (tmp[i] == 1) {
				sum += number[i + 1];
			}
			if (tmp[i] == 2) {
				sum -= number[i + 1];
			}
			if (tmp[i] == 3) {
				sum *= number[i + 1];
			}
			if (tmp[i] == 4) {
				if (sum < 0) {
					sum *= -1;
					sum /= number[i + 1];
					sum *= -1;
				}
				else {
					sum /= number[i + 1];
				}
			}
		}
		if (min_result > sum) min_result = sum;
		if (max_result < sum) max_result = sum;
		return;
	}

	for (int s = 1; s <= 4; s++) {
		if (operators[s]) {
			operators[s]--;
			tmp[depth] = s;
			solve(depth + 1);
			tmp[depth] = 0;
			operators[s]++;
		}
	}
}