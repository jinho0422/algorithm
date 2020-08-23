#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
char str[1004];
char board[1004][1004];
bool Jcheck[1004][1004];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int moveResult;
bool flag;
// �Ұ� �������� ��ġ�� Ȯ���ϱ� ���� struct..
typedef struct _pos {
	int h, y;
}pos;

queue<pos> fQ; // ���� ��ġ�� �����ϱ� ���� queue
queue<pos> jQ; // �������� ������ ��ġ�� �����ϱ� ���� queue

void BFS();

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'F') fQ.push(pos({ hang, yal })); // ���̸� fQ�� ��ġ ����
			
			if (board[hang][yal] == 'J') { // �����̸� jQ�� ��ġ ����
				Jcheck[hang][yal] = true;
				jQ.push(pos({ hang, yal }));
			}
		}
	}
	BFS();
	if (!flag) printf("IMPOSSIBLE\n"); // Ż���� �������� ������ ���..
	return 0;
}

void BFS() {
	moveResult = 1; // �����̰� ������ �����..
	while (!jQ.empty()) { // �����̰� ������ �� �ִ� ��ġ�� ����������..
		int fsz = fQ.size(); // fQ�� ũ�⸸ŭ ���� ������ �� �ִ� ���� ã�´�..
		for (int s = 0; s < fsz; s++) {
			pos fp = fQ.front();
			fQ.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = fp.h + dirY[dir];
				int newX = fp.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// ������ ���ִ� ��ġ�� J �̰ų� . �̸� ����ġ�� F�� �����ϰ� ���� �����δ�..
				if (board[newY][newX] == 'J' || board[newY][newX] == '.') {
					board[newY][newX] = 'F';
					fQ.push(pos({ newY, newX }));
				}
			}
		}

		int jsz = jQ.size();
		for (int s = 0; s < jsz; s++) {
			pos jp = jQ.front();
			jQ.pop();
			if (jp.h == 0 || jp.h == N - 1 || jp.y == 0 || jp.y == M - 1) { // ������ ���ʿ� ������ Ż�� �� �� �����Ƿ� ������� ����Ѵ�..
				printf("%d\n", moveResult);
				flag = true;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				int newY = jp.h + dirY[dir];
				int newX = jp.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] == '.' && !Jcheck[newY][newX]) { // �����̰� ���� ���� �ƴϰ� '.'�̸� �����δ�..
					Jcheck[newY][newX] = true;
					jQ.push(pos({ newY, newX }));
					board[newY][newX] = 'J'; // �������� �־��ְ�
					if (board[jp.h][jp.y] == 'J') board[jp.h][jp.y] = '.'; // ���� �����̰� �ִ����ε� ���� �Űܺپ��ٸ� �״�� ���� J�� ������ '.'���� �ٲ��ش�.
				}
			}
		}
		moveResult++;
	}
}