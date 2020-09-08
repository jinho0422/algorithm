#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
char str[104];
char board[104][104];
bool check[104][104];
bool keyFlag[27];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool flag;
int result;

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;

void BFS(int hang, int yal);

int main() {
	//�Է�
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//�ʱ�ȭ
		result = 0;
		memset(board, '.', sizeof(board)); // �������� 0, 0���� �ϱ� ���� ������ ���� �� �� �ִ� '.'�� �س��´�.
		memset(keyFlag, false, sizeof(keyFlag));
		scanf("%d %d", &N, &M);
		for (int hang = 1; hang <= N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang][yal + 1] = str[yal];
			}
		}
		scanf("%s", str);
		// ���踦 keyFlag�� ���ؼ� �ִ��� ������ �Ǵ�.. true : ���� ���� false : ���� ����
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] == '0') break;
			keyFlag[str[i] - 'a'] = true;
		}

		while (1) {
			flag = false; // BFS�� ���鼭 ���� ���踦 ã���� flag : true, �ƴϸ� flag : false
			while (!Q.empty()) Q.pop(); // queue�ʱ�ȭ
			memset(check, false, sizeof(check)); // �湮üũ�ʱ�ȭ
			BFS(0, 0);
			if (!flag) break;
		}
		//���
		printf("%d\n", result);
	}
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N + 1 || newX < 0 || newX > M + 1) continue;
			// �������� �ִ� ��
			if (board[newY][newX] == '.' && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
			// ������ ã�� ��
			else if (board[newY][newX] == '$' && !check[newY][newX]) {
				check[newY][newX] = true;
				result++;
				board[newY][newX] = '.';
				Q.push(pos({ newY, newX }));
				
			}
			// ���踦 ������ ��
			else if (board[newY][newX] >= 'a' && board[newY][newX] <= 'z' && !check[newY][newX]) {
				check[newY][newX] = true;
				keyFlag[board[newY][newX] - 'a'] = true;
				board[newY][newX] = '.';
				flag = true;
				Q.push(pos({ newY, newX }));
			}
			// ����� ���� ���� ��
			else if (board[newY][newX] >= 'A' && board[newY][newX] <= 'Z' && !check[newY][newX]) {
				if (keyFlag[board[newY][newX] - 'A']) {
					check[newY][newX] = true;
					board[newY][newX] = '.';
					Q.push(pos({ newY, newX }));
					
				}
			}
		}
	}
}