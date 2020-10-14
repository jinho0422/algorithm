#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;
int N;
int board[17][17];
bool check[17][17];
int dirY[3] = { 0, 1, 1 }; // 0 : ������, 1 : �밢������, 2: �Ʒ���
int dirX[3] = { 1, 1, 0 };
int result;

void DFS(int hang, int yal, int d, int f);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	check[0][0] = check[0][1] = true;
	// ������ ��(1)�� �ƴϸ� DFS
	if(board[N -1][N -1] == 0) DFS(0, 1, 0, N - 1); // hang, yal, �����̴� ����, ������ ��
	//���
	printf("%d\n", result);
	return 0;
}
// ������ ��ġ���� ������ �Ʒ��� �밢�������� ��� �ƹ��͵� ������ true ��ȯ
bool moveCheck(int hang, int yal) {

	for (int dir = 0; dir < 3; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1 || check[newY][newX]) return false;
	}
	return true;
}

void DFS(int hang, int yal, int d, int f) {
	//���������� �����ϸ� ����� + 1
	if (hang == N - 1 && yal == N - 1) {
		result++;
		return;
	}
	//������ �����̴� ������ ����
	for (int dir = 0; dir < 3; dir++) {
		if ((d == 0 && dir == 2) || d == 2 && dir == 0) continue; // ������ ���η� �������� ���η� ��������������, �ݴ�ε� �������Ƿ� continue
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];
		// �Ʒ��ʰ� ���������� �������� �̵��Ҷ�
		if (dir == 0 || dir == 2) {
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) continue;
			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				DFS(newY, newX, dir, f);
				check[newY][newX] = false;
			}
		}
		//�밢������ �̵��Ҷ�
		else if (dir == 1) {
			bool flag = moveCheck(hang, yal);
			//true�̸� �밢������ ������ �̵�����..
			if (flag) {
				for (int d = 0; d < 3; d++) check[hang + dirY[d]][yal + dirX[d]] = true;		
				DFS(newY, newX, dir, f);
				for (int d = 0; d < 3; d++) check[hang + dirY[d]][yal + dirX[d]] = false;
			}
		}
	}
}