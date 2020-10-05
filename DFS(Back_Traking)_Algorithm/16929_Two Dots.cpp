#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[51][51];
int dirY[4] = { 0, 1, 0, -1 }; // ������ ��, ��, ��, �� ���� �ϴ� ���� �ð��� ���̴µ� ȿ�����̴�.
int dirX[4] = { 1, 0, -1, 0 };
bool flag;

void DFS(int depth, int hang, int yal, int fh, int fy);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	for (int hang = 0; hang < N -1; hang++) {
		for (int yal = 0; yal < M -1; yal++) {
			DFS(1, hang, yal, hang, yal); // ����� ���� �����, ���� hang, yal, ������ �Ǿ����� �Ǵ��ϱ� ���� hang, yal
			//����Ǿ�����
			if (flag) {
				printf("Yes\n");
				return 0;
			}
		}
	}
	//�ϳ��� �����ϴ� ���� ������..
	printf("No\n");
	return 0;
}

void DFS(int depth, int hang, int yal, int fh, int fy) {
	if (flag) return;
	if (depth >= 4 && hang == fh && yal == fy) {
		flag = true;
		return;
	}
	for (int dir = 0; dir < 4; dir++) {
		
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 ) continue;

		if (!check[newY][newX] && board[newY][newX] == board[fh][fy]) {
			check[newY][newX] = true;
			DFS(depth + 1, newY, newX, fh, fy);
			check[newY][newX] = false;
		}
	}
}