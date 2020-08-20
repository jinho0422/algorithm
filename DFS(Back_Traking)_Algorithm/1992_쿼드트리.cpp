#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;
char str[65];
int board[65][65];
queue<int> Q;


void DFS(int H, int Y, int size);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
		}
	}
	DFS(0, 0, N);
	//Q�� �ϳ��� ���鼭 -1�̸� (�� -2�̸� ) �ٸ� ���̸� Q���� ����Ʈ�Ѵ�..
	while (!Q.empty()) {
		if (Q.front() == -1) printf("(");
		else if (Q.front() == -2) printf(")");
		else printf("%d", Q.front());
		Q.pop();
	}
	printf("\n");
	return 0;
}

void DFS(int H, int Y, int size) {
	int tmp = board[H][Y]; // �񱳴��
	bool check = false; // �� �簢���� �Ȱ��� ���� ������ �ִ��� �Ǵ�..
	// ���������� size == 1�̸� Q�� ���� �־��ش�..
	if (size == 1) {
		Q.push(tmp);
		return;
	}
	// ũ�⸦ ���鼭 ��� �Ȱ��� ������ �Ǵ�
	for (int hang = H; hang < H + size; hang++) {
		for (int yal = Y; yal < Y + size; yal++) {
			if (tmp != board[hang][yal]) {
				check = true;
				break;
			}
		}
	}
	//���� ��� �Ȱ��� ���̶�� Q�� �־��ش�..
	if (!check) {
		Q.push(tmp);
		return;
	}
	Q.push(-1); // (�� �����ϱ�����
	// 4��и��� ��ͷ� �����ش�..
	DFS(H, Y, size / 2);
	DFS(H, Y + size / 2, size / 2);
	DFS(H + size / 2, Y, size / 2);
	DFS(H + size / 2, Y + size / 2, size / 2);
	Q.push(-2); // )�� �����ϱ�����
}