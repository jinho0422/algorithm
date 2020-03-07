/*
	N*M���翡 '.'�� �� ����, '#'�� ��Ÿ��, 'o' �� ��, 'v'�� �����̴�.
	��Ÿ���׿��ִ� ������ �㿡 ��� ������ ���� ����ؼ� ������ ���� ���ų� ������ ���� �� ��������
	���� ���� �� ������ ���밡 �� ��������..
	��ħ�� �Ǿ��� �� ��� ������ ���� ã�� �˰����� �����ض�..

	��Ÿ�� ���� ��� ���븦 ����ؾߵǹǷ� BFS�� ����Ͽ� Ž���ϸ鼭 ��� ������ ���� ����Ͽ�
	��ü�� ����� ���� ������ ���� �˰��� ����..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
char str[251];
char board[251][251];
bool check[250][250];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int sheep;// ��ü ���� ���� ��������..
int wolf; // ��ü ������ ���� ��������..

typedef struct _pos {
	int h, y;
	char c;
}pos;

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'v') wolf++; // ��ü ������ ��..
			if (board[hang][yal] == 'o') sheep++;  // ��ü ���� ��..
		}
	}

	for (int hang = 0; hang < N; hang++) { // ������ ���鼭 �� or ���밡 ��Ÿ���� BFSŽ��..
		for (int yal = 0; yal < M; yal++) {
			if (!check[hang][yal]) {
				if (board[hang][yal] == 'v' || board[hang][yal] == 'o') {
					BFS(hang, yal);
				}
			}
		}
	}

	printf("%d %d\n", sheep, wolf);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal, board[hang][yal] }));
	int cnt_sheep = 0; // ��Ÿ������ ���� ���� ����ϱ�����
	int cnt_wolf = 0; // ��Ÿ�� ���� ������ ���� ����ϱ�����..


	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		if (p.c == 'v') cnt_wolf++; 
		if (p.c == 'o') cnt_sheep++;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

			if (board[newY][newX] == '.' && !check[newY][newX]) { // ����� ��
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
			if (board[newY][newX] == 'v' && !check[newY][newX]) { // ������ ��..
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
			if (board[newY][newX] == 'o' && !check[newY][newX]) { // ���� ��..
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, board[newY][newX] }));
			}
		}
	}

	if (cnt_wolf >= cnt_sheep) sheep -= cnt_sheep; // ������ ���� ũ�ų� ������ ��ü�� ���� ������ ��Ÿ�� ���� ���� ���� ����..
	else wolf -= cnt_wolf; // ���� ���� �� ������ ��ü�� ������ ������ ��Ÿ�� ���� ������ ���� ����..
}