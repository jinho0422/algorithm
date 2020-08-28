#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int x, y;

int main() {
	scanf("%d %d", &x, &y);
	if (x > 0 && y > 0) printf("1\n");
	else if (x < 0 && y > 0) printf("2\n");
	else if (x < 0 && y < 0) printf("3\n");
	else printf("4\n");

	return 0;
}