#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int A, B;

int main() {
	scanf("%d %d", &A, &B);
	if (A > B) printf(">\n");
	else if (A < B) printf("<\n");
	else if (A == B) printf("==\n");

	return 0;
}