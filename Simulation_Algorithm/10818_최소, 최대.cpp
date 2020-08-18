#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int maxNum;
int minNum;

int main() {
	scanf("%d", &N);

	for (int a, s = 0; s < N; s++) {
		scanf("%d", &a);
		if (s == 0) {
			maxNum = a, minNum = a;
		}
		else {
			maxNum = max(maxNum, a);
			minNum = min(minNum, a);
		}
	}
	printf("%d %d\n", minNum, maxNum);

	return 0;
}