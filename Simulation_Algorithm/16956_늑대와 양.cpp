#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
char str[502];
char board[502][502];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '.') board[hang][yal] = 'D'; // ���밡 ������ �� �ִ� ���� ��Ÿ���� ģ��..
			if (board[hang][yal] == 'W') { // �����̸� �ִ´�..
				Q.push(pos({ hang, yal }));
			}
		}
	}
	int sz = Q.size();
	for (int s = 0; s < sz; s++) { // ������ ��ġ���� �����¿츦 ���� ���� �ִ����� �Ǵ�..
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
			 // ���� �� ���..
			if (board[newY][newX] == 'S') {
				printf("0\n");
				return 0;
			}
		}
	}
	// ��� ���ٸ� ���..
	printf("1\n");
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			printf("%c", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
	// ��� �� ������ ���� ���� �����¿츦 ���� ���밡 ������ 0�� ����ϰ� ������ '.'�� 'D'�� ��Ÿ���� ���� �������� ����ϸ� �ð��� �� ����� ���̴�.
}
