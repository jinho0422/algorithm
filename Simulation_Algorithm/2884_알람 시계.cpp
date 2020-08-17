#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int H, M;

int main() {
	scanf("%d %d", &H, &M);
	int nextM = M - 45;
	if (nextM < 0) {
		H--;
		M = M + 60 - 45;
	}
	else M -= 45;

	if (H < 0) H = 23;
	printf("%d %d\n", H, M);
		
	return 0;
}