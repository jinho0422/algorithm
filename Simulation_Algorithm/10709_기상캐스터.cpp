#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[102];
char board[102][102];

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	// board를 돌면서
	for (int hang = 0; hang < N; hang++) {
		bool findCloud  = false; // 각 행마다 구름이 있었던 적이 있으면 true 아니면 false
		int minute = 0;
		for (int yal = 0; yal < M; yal++) {
			// 구름이 아닐때 구름이 한번도 나타나지 않았으면 -1, 구름이 나타났던적이 있으면 minute를 출력
			if (board[hang][yal] == '.') {
				if (!findCloud) printf("-1 ");
				else {
					printf("%d ", minute);
					minute++;
				}
			}	
			// 구름을 만나면 findCloud == true, minute를 새로 갱신한다.
			if (board[hang][yal] == 'c') {
				findCloud = true;
				minute = 0;
				printf("%d ", minute);
				minute++;
			}
		}
		printf("\n");
	}
	return 0;
}