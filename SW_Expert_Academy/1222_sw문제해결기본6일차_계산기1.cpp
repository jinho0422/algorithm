#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int result;
char str;

int main() {
	freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		result = 0;
		scanf("%d", &N);
		for (int s = 0; s < N; s++) {
			scanf("%c", &str);
			if (str > '9' || str <'0') continue;
			result += str - '0';
		}
		printf("#%d %d\n", t, result);
	}

	return 0;
}