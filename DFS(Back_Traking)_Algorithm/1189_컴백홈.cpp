#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, K;
char str[7];
char board[7][7];
bool check[7][7];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;

void DFS(int depth, int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	//ó�� ����ϴ� ���� �Ʒ����� �湮üũ..
	check[N - 1][0] = true;
	DFS(0, N - 1, 0);
	check[N - 1][0] = false;

	printf("%d\n", result);
	return 0;
}

void DFS(int depth, int hang, int yal) {
	//������ Ƚ���� ó���ڸ� ���� K���̹Ƿ� K -1��°�̰� ������ �����̸� ������� ����..
	if (hang == 0 && yal == M - 1 && depth == K -1) {
		result++;
		return;
	}
	//������ ������ �����¿츦 ���� ������ �� �ִ� ���� �Ǵ�..
	for (int dir = 0; dir < 4; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

		if (board[newY][newX] == '.' && !check[newY][newX]) {
			check[newY][newX] = true; // ������ ���� �湮üũ���ְ�
			DFS(depth + 1, newY, newX); // ���..
			check[newY][newX] = false;
		}
	}
}