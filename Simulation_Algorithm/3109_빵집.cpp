#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[502];
char board[10002][502];
bool check[10002][502];
int dirY[3] = { -1, 0, 1 };
int dirX[3] = { 1, 1, 1 };
int result;
bool flag;
bool resultFlag;

typedef struct _pos {
	int h, y;
}pos;

void DFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	// ���� �� ������ DFS�� �� �����ʱ��� �� �� �ִ��� Ȯ��..
	for (int hang = 0; hang < N; hang++) {
		flag = false; //  �������� �� �����ʱ��� ������ Ȯ���ϴ� flag
		DFS(hang, 0);
		if (resultFlag) break; // �������� ��ġ�ϴ� ���� ������ �� �밢��, ������, ������ �Ʒ� �밢������ �����Ƿ�
	}
	//���
	printf("%d\n", result);
	return 0;
}

void DFS(int hang, int yal) {
	if (flag) return; // �������� ��ġ������ return..
	if (resultFlag) return; // ���̻� �������� ������ �� �������� return..
	if (yal == M - 1) { // �� ������ ���� �������� ����Ǿ�����..
		result++;
		flag = true;
		return;
	}
	for (int dir = 0; dir < 3; dir++) {
		if (flag) return; // �������� ��ġ������ return..
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) {
			if (newX == M) resultFlag = true; // ���� ���� �������� ��ԵǸ� �� �ؿ��� �������� ���̻� ��ġ�� �� �����Ƿ� resultFlag true�� �س��� ����������.
			continue;
		}
		if (!check[newY][newX] && board[newY][newX] == '.') {
			check[newY][newX] = true;
			DFS(newY, newX);
		}
	}
}