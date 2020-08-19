#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

char str[102];
int result[30];

int main() {
	scanf("%s", str);
	for (int s = 0; str[s] != '\0'; s++) {
		result[str[s] - 'a']++;
	}
	for (int s = 0; s < 26; s++) {
		printf("%d ", result[s]);
	}
	printf("\n");
	return 0;
}