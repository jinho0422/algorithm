#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[51][51];
bool waterCheck[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;
bool flag;

typedef struct _pos {
	int h, y; // h : hang, y : yal
}pos;
pos endd[1]; // �������� ����
queue<pos> water;
queue<pos> Q;

void BFS();

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			//water�� ��� water queue�� ����
			if (board[hang][yal] == '*') {
				waterCheck[hang][yal] = true;
				water.push(pos({ hang, yal }));
			}
			// ����ġ�� ��� Q queue�� ����
			else if (board[hang][yal] == 'S') {
				check[hang][yal] = true;
				Q.push(pos({ hang, yal }));
			}
			// ����� ���� ��� �������� ����..
			else if (board[hang][yal] == 'D') {
				endd[0] = { hang, yal };
			}
		}
	}
	BFS();
	//���
	if (!flag) printf("KAKTUS\n");
	else printf("%d\n", result);
	return 0;
}

void BFS() {

	while (!Q.empty() || !water.empty()) {
		//water�� size��ŭ �����鼭(���� ������)
		int wsz = water.size();
		for (int s = 0; s < wsz; s++) {
			pos p = water.front();
			water.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// ���̰ų� ���ÿ� �����̹Ƿ� S�ΰ�� ���� ä���..
				if (!waterCheck[newY][newX] && (board[newY][newX] == '.' || board[newY][newX] == 'S')) {
					waterCheck[newY][newX] = true;
					board[newY][newX] = '*';
					water.push(pos({ newY, newX}));
				}
			}
		}
		// ����ġ�� �������� Q�� szie��ū �����鼭
		int ssz = Q.size();
		for (int s = 0; s < ssz; s++) {
			pos p = Q.front();
			Q.pop();
			// ���� ���������̸� Ż��..
			if (p.h == endd[0].h && p.y == endd[0].y) {
				flag = true;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// ���̰ų� ����� ���̸� 
				if (!check[newY][newX] && (board[newY][newX] == '.' || board[newY][newX] == 'D')) {
					board[p.h][p.y] = '.'; // ���� �ü����ֱ⶧���� ����ġ�� ������ �����
					board[newY][newX] = 'S'; // ������ �̵����� ����ġ�� �̵�
					check[newY][newX] = true;
					Q.push(pos({ newY, newX}));
				}
			}
		}
		result++; // ����� ����
	}
}