#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int result;


int main() {
	//입력
	scanf("%d %d", &N, &M);
	// N(행)의 크기에 따라 N의 크기가 1이면 나이트가 위, 아래로 이동할 수 없으므로 결과값은 1.
	if (N == 1) {
		result = 1;
	}
	// N의 값이 2이면 위 아래로 움직일 수 있는 크기가 1이므로 오른쪽으로 쉬프트 되는 값는 2씩이다. 그리고 결과값이 4이상을 넘어갈 수 없다.
	else if (N == 2) {
		result = (M - 1) / 2 + 1;
		if (result > 4) result = 4;
	}
	// N의 값이 3이상이면 M의 값에 따라 만약 M이 6보다 크면 나이트가 4 방향을 다 움직이고 오른쪽 쉬프트를 1칸씩하면서 움직일 수 있다. 
	// M이 6이하이면 오른쪽 쉬프트를 한 칸씩하면서 결과값의 최대는 4까지 밖에 갈 수 가 없다.
	else {
		if (M > 6) {
			result = (M - 6) + 4;
		}
		else {
			result = (M - 1) + 1;
			if (result > 4) result = 4;
		}
	}
	printf("%d\n", result);
	return 0;
}

