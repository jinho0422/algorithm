#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[1 << 5][51][51]; // ��Ʈ����ũ�� ��������..
int dirY[4] = { -1, 0, 0 ,1 };
int dirX[4] = { 0, -1, 1, 0 };
int checkX;

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : ��Ʈ����ũ��
}pos;
pos starts[1]; // ����� ����
pos endd[1]; // ������ ����..
queue<pos> Q;

int BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d %d", &M, &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'S') {
				board[hang][yal] = '.';
				starts[0] = { hang, yal, 0 };
			}
			if (board[hang][yal] == 'E') {
				board[hang][yal] = '.';
				endd[0] = { hang, yal, 0 };
			}
			if (board[hang][yal] == 'X') {
				board[hang][yal] = checkX + '0';
				checkX++;
			}
		}
	}
	//���
	printf("%d\n", BFS(starts[0].h, starts[0].y));
	return 0;
}

int BFS(int hang, int yal) {
	check[0][hang][yal] = true;
	Q.push(pos({ hang, yal, 0 }));
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			// ���� ��� ������ �� ã�� ���������� �����ϸ� time�� ����..
			if (p.cnt == pow(2, checkX) - 1) {
				if (p.h == endd[0].h && p.y == endd[0].y) {
					return time;
				}
			}

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;
				// ������ ���°��̵�
				if (board[newY][newX] == '.' && !check[p.cnt][newY][newX]) {
					check[p.cnt][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt }));
				}
				//������ �ִ� �� �̵�
				if (board[newY][newX] != '.' && !check[p.cnt][newY][newX]) {
					int newCnt = p.cnt | 1 << board[newY][newX] - '0';
					if (!check[newCnt][newY][newX]) {
						check[newCnt][newY][newX] = true;
						Q.push(pos({ newY, newX, newCnt }));
					}
				}
			}
		}
		time++;
	}
}