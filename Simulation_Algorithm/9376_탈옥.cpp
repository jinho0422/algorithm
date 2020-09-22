#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
char str[105];
char board[105][105];
bool check[3][105][105];
int doorCnt[3][105][105]; // �˼� 0, �˼� 1, ���� �����ִ� ��� 2 �� ���� ���� ���� �� ������ ĭ���� �����ִ� �迭..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result[105][105]; // 3����� ���� ���� ������ ���� ���� �迭..
int minResult;

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : ���� ������ ����..
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};

vector<pos> Vec;
priority_queue<pos, vector<pos>, cmp> Q; // �켱���� ť�� �� ������ �ּ������� ���� ���� �� ��츦 doorCnt�� �����ϱ�����..

void BFS(int hang, int yal, int type);

int main() {
	//�Է�
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//�ʱ�ȭ..
		minResult = 987654321;
		scanf("%d %d", &N, &M);
		memset(board, '.', sizeof(board));
		memset(check, false, sizeof(check));
		memset(doorCnt, 0, sizeof(doorCnt));
		memset(result, 0, sizeof(result));
		Vec.clear();

		int num = 1;
		Vec.push_back(pos({ 0, 0, 0 })); // ���� �����ִ� ��� 2
		for (int hang = 0; hang < N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang + 1][yal + 1] = str[yal];
				if (board[hang + 1][yal + 1] == '$') {
					board[hang + 1][yal + 1] = '.';
					Vec.push_back(pos({ hang + 1, yal + 1, num++ })); // �˼� 0, �˼� 1
				}
				if (board[hang + 1][yal + 1] == '*') result[hang + 1][yal + 1] = -1; // ��������� ���ֱ����� '*'�̸� ������� -1�� ����..
			}
		}
		//3���� ����� �ּ� ��� ���� ���� ������ ������ �ڸ��� �����ϴ� BFS..
		for (int s = 0; s < Vec.size(); s++) BFS(Vec[s].h, Vec[s].y, Vec[s].cnt);

		// 3����� �ּ� ��� ���� ���� �������� ��� �����ش�..
		for (int hang = 1; hang < N + 1; hang++) {
			for (int yal = 1; yal < M + 1; yal++) {
				for (int i = 0; i < 3; i++) {
					result[hang][yal] += doorCnt[i][hang][yal];
				}
				if (board[hang][yal] == '#') result[hang][yal] -= 2; // ���̿��� ���� 3����  ��� + 1�� �������Ƿ� -2�� ���ش�..
				if (result[hang][yal] != -1) {
					if (minResult > result[hang][yal]) minResult = result[hang][yal];
				}
			}
		}
		//���
		printf("%d\n", minResult);
	}
	return 0;
}

void BFS(int hang, int yal, int type) {
	check[type][hang][yal] = true;
	doorCnt[type][hang][yal] = 0;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N + 1 || newX < 0 || newX > M + 1) continue;
			//���������ִ°�.
			if (!check[type][newY][newX] && board[newY][newX] == '.') {
				check[type][newY][newX] = true;
				doorCnt[type][newY][newX] = p.cnt;
				Q.push(pos({ newY, newX, p.cnt }));
			}
			// ���ΰ��
			if (!check[type][newY][newX] && board[newY][newX] == '#') {
				check[type][newY][newX] = true;
				int newCnt = p.cnt + 1;
				doorCnt[type][newY][newX] = newCnt;
				Q.push(pos({ newY, newX, newCnt }));
			}
		}
	}
}