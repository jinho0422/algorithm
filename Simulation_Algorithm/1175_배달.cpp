#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[1<< 2][5][51][51];
int dirY[5] = { 0, 1, 0, 0, -1 };
int dirX[5] = { 0, 0, -1, 1, 0 };
char dev;

typedef struct _pos {
	int h, y, d, cnt;

}pos;
queue<pos> Q;

int BFS();

int main() {
	dev = 'a';
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'S') { // ����ġ�� queue�� �־��ְ� '.'�� �ٲ��ش�.
				board[hang][yal] = '.';
				Q.push(pos({ hang, yal, 0, 0 }));
				check[0][0][hang][yal] = true;
			}
			else if (board[hang][yal] == 'C') { // ���� �����̸� �����Ǽ����� ������� �˱����� 'a', 'b'�� �д�.
				board[hang][yal] = dev++;
			}
		}
	}
	//���
	printf("%d\n", BFS());
	return 0;
}

int BFS() {
	int time = 0; // �����
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			if (p.cnt == 3) return time; // �ΰ��� ������ �� ã���� return.. p.cnt == 3 �̶�� ���� �������� 11�ε� 2*1 + 1 * 1�̴�.

			for (int dir = 1; dir < 5; dir++) {
				if (p.d == dir) continue;
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == '#') continue;

				if (board[newY][newX] == '.' && !check[p.cnt][dir][newY][newX]) {
					check[p.cnt][dir][newY][newX] = true;
					Q.push(pos({ newY, newX, dir, p.cnt}));
				}
				//���� �����̸� check������ �ٲ��ش�..
				if (board[newY][newX] != '.' && !check[p.cnt][dir][newY][newX]) {
					int newCnt = p.cnt | 1 << (board[newY][newX] - 'a');
					check[newCnt][dir][newY][newX] = true;
					Q.push(pos({ newY, newX, dir,newCnt }));
				}
			}
		}
		time++;
	}
	return -1;
}