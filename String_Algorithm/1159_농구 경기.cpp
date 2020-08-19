#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
char str[32];
int firstName[26];
bool flag;

int main() {
	scanf("%d", &N);
	for (int s = 0; s < N; s++) {
		scanf("%s", str);
		firstName[str[0] - 'a']++;
	}
	for (int s = 0; s < 26; s++) {
		if (firstName[s] >= 5) {
			flag = true;
			printf("%c", 'a' + s);
		}
	}
	if (!flag) printf("PREDAJA");
	printf("\n");

	return 0;
}