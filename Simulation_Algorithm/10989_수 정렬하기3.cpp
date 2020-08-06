#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int numbers[10001];
int maxNum;

int main() {
	//입력
	int N; scanf("%d", &N);
	
	for (int num, s = 0; s < N; s++) {
		scanf("%d", &num);
		//수의 최고값 갱신..
		if (maxNum < num) maxNum = num;
		// 수의 갯수 세기..
		numbers[num]++;
	}
	// 1부터 최고값까지 수의 갯수를 출력..
	for (int s = 1; s <= maxNum; s++) {
		for (int i = 0; i < numbers[s]; i++) {
			printf("%d\n", s);
		}
	}

	return 0;
}