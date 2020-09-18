#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[1<<6][51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y, cnt; //  h : hang, y : yal, cnt : bit ����� ����..
}pos;

queue<pos> Q;

int BFS();

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '0') { // �ʱ� ��ġ�� ������ '.'���� �ٲٰ� Queue�� �ִ´�.
				board[hang][yal] = '.';
				Q.push(pos({ hang, yal, 0 }));
				check[0][hang][yal] = true;
			}
		}
	}
	printf("%d", BFS());
	return 0;
}

int BFS() {
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();// queue size��ŭ ���鼭..
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			if (board[p.h][p.y] == '1') { // ���� ���������̸� time ����� ����..
				return time;
			}

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// '.' �ƹ��͵� ���� �� , '1'�� ���������� ��������
				if (!check[p.cnt][newY][newX] && (board[newY][newX] == '.' || board[newY][newX] == '1')) {
					check[p.cnt][newY][newX] = true;
					Q.push(pos({ newY, newX, p.cnt }));
				}
				// ���踦 ������ bit������� ���踦 ȹ��..
				if (!check[p.cnt][newY][newX] && (board[newY][newX] >= 'a' && board[newY][newX] <= 'f')) {
					int newCnt = p.cnt | (1 << board[newY][newX] - 'a');
					if (!check[newCnt][newY][newX]) {
						check[newCnt][newY][newX] = true;
						Q.push(pos({ newY, newX, newCnt }));
					}
				}
				//���� ������ ���谡 �ִ��� üũ�Ѵ�..
				if (!check[p.cnt][newY][newX] && (board[newY][newX] >= 'A' && board[newY][newX] <= 'F')) {
					if (p.cnt & (1 << board[newY][newX] - 'A')) {
						check[p.cnt][newY][newX] = true;
						Q.push(pos({ newY, newX, p.cnt }));
					}
				}
			}
		}
		time++;
	}
	//���� ������ �湮�ߴµ� '1'�������� �������ٸ� -1 return..
	return -1;
}