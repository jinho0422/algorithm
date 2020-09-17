#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, K;
int boardA[101][101];
int boardB[101][101];

int main() {
	//��� A, ��� B�� �Է�
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
	// ���A�� N * M, ���B�� M * K �̹Ƿ� A�� �� ��� B�� �� ���� ���ϸ鼭 ����� �Ѵ�. 
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