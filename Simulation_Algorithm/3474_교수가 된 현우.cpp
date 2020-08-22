#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int N;

// 오른쪽에 0 이 나오기 위해서는 2, 5가 필요하다 그 중에서 작은 수를 선택하면
// 오른쪽에 0이 몇개 인지 판단할 수 있다.(소인수 분해를 통해 2, 5의 갯수를 각각 세어준다)
int main() {
	scanf("%d", &N);
	for (int fac, i = 0; i < N; i++) {
		int two = 0, five = 0;
		scanf("%d", &fac);
		for (int j = 2; j <= fac; j *= 2) {
			two += fac / j;
		}
		//예를 들어 25는 5가 2개이다 따라서 만약 N이 30이면 25는 j == 5 일때 5가 하나 플러스되고 j == 25일 때 또 플러스된다.
		for (int j = 5; j <= fac; j *= 5) {
			five += fac / j;
		}
		printf("%d\n", min(two, five));
	}
	return 0;
}