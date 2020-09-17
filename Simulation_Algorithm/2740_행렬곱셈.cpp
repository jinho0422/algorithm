#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, K;
int boardA[101][101];
int boardB[101][101];

int main() {
	//행렬 A, 행렬 B를 입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &boardA[hang][yal]);
		}
	}
	scanf("%d %d", &M, &K);
	for (int hang = 0; hang < M; hang++) {
		for (int yal = 0; yal < K; yal++) {
			scanf("%d", &boardB[hang][yal]);
		}
	}
	// 행렬A는 N * M, 행렬B는 M * K 이므로 A의 한 행과 B의 한 열을 곱하면서 출력을 한다. 
	for (int hang = 0; hang < N; hang++) {
		for (int i = 0; i < K; i++) {
			int sum = 0;
			for (int yal = 0; yal < M; yal++) {
				sum += (boardA[hang][yal] * boardB[yal][i]);
			}
			printf("%d ", sum);
		}
		printf("\n");
	}

	return 0;
}