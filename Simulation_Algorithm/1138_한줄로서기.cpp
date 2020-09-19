#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;
int line[11];
int result[11]; // 결과값을 갱신하기 위한 배열
int N;

int main() {
	//입력
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &line[i]);
	}

	for (int i = 1; i <= N; i++) { // 1~N까지 사람들을 보면서
		int left = 0; // 왼쪽편에 result의 0의 갯수를 count갯수 변수..
		for (int j = 0; j < N; j++) {
			if (result[j] == 0) { 
				if (left == line[i]) { //만약 left가 i의 왼쪽에 있는 큰 사람의 갯수랑 같으면
					result[j] = i; // 결과값 갱신..
					break;
				}
				else left++; // 아니면 left에 큰 사람이 있다고 conut한다.
			}
		}
	}
	//출력
	for (int i = 0; i < N; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
}