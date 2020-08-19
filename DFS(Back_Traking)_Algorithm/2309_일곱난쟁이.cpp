#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>

using namespace std;

int board[9];
int result[8];
bool flag;

void DFS(int depth, int start, int sum);

int main() {
	//�Է�
	for (int i = 0; i < 9; i++) {
		scanf("%d", &board[i]);
	}
	// ������������ ������ ����� ����..
	sort(board, board + 9);
	// 7���� �������� Ű�� ���ϱ� ���� DFS
	DFS(0, 0, 0);

	return 0;
}

void DFS(int depth, int start, int sum) {
	// �������� Ű��100�̸� �������ʹ� ����, sum 100���� ũ�� return, �����̰� 7���� �Ѿ�� return
	if (flag) return;
	if (sum > 100) return;
	if (depth > 7) return;
	if (depth == 7 && sum == 100) {
		flag = true;
		for (int i = 0; i < 7; i++) {
			printf("%d\n", result[i]);
		}
		return;
	}
	// 9���� ������ �߿� 7���� �������� �̱�.
	for (int s = start; s < 9; s++) {
		sum += board[s];
		result[depth] = board[s];
		DFS(depth + 1, s + 1, sum);
		sum -= board[s];
	}
}