#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int year;

int main() {
	scanf("%d", &year);
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) printf("1\n");
	else printf("0\n");

	return 0;
}