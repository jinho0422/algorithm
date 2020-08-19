#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int A, B, C;
int carNum[101];
int result;

int main() {
	scanf("%d %d %d", &A, &B, &C);
	for (int f, e, s = 0; s < 3; s++) {
		scanf("%d %d", &f, &e);
		for (int i = f; i < e; i++) {
			carNum[i]++;
		}
	}
	for (int s = 1; s < 101; s++) {
		if (carNum[s] == 0) continue;
		if (carNum[s] == 1) result += A;
		if (carNum[s] == 2) result += B * 2;
		if (carNum[s] == 3) result += C * 3;
	}
	printf("%d\n", result);
	return 0;
}