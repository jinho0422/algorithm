#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M, K;
int board[11][11]; // ������ ��� �迭
int tmpBoard[11][11]; // �ܿ￡ �� ����� ������ �ִ� �迭
int dirY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dirX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int result;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec; // ������ �� �ִ� ������ hang, yal�� �־��ش�..

deque<int> Q[11][11]; // ������� ������ �ִ��� �Ǵ��ϴ� deque

void spring();
void fall();
void winter();

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &tmpBoard[hang][yal]);
			board[hang][yal] = 5;
		}
	}
	//�����ɱ�
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a -1][b -1].push_back(c);
	}
	//�⵵�� �����鼭
	for (int i = 0; i < K; i++) {
		spring();
		if(Vec.size() != 0) fall();
		winter();
		if (result == 0) break; // ���� ��Ƴ��� ������ ������ break;;
	}
	//���
	printf("%d\n", result);
	return 0;
}
//���� ����
void spring() {
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			int sz = Q[hang][yal].size();
			if (sz == 0) continue;
			bool flag = false; // flag : false�̸� ����� �԰�, true�̸� ����� �����.
			for (int i = 0; i < sz; i++) {
				int p = Q[hang][yal].front();
				Q[hang][yal].pop_front();
				if (!flag) {
					if (board[hang][yal] >= p) {
						board[hang][yal] -= p;
						Q[hang][yal].push_back(p + 1);
						if ((p + 1) % 5 == 0) Vec.push_back(pos({ hang, yal }));
					}
					else {
						board[hang][yal] += p / 2;
						flag = true;
					}
				}
				else board[hang][yal] += p / 2;
			}
		}
	}
}
// ���� ���� ������ �����鼭 ���̰� 5�� ������� �������� Vec�� �־� ���Ľ�Ų��.
void fall() {
	for (int s = 0; s < Vec.size(); s++) {
		for (int dir = 0; dir < 8; dir++) {
			int newY = Vec[s].h + dirY[dir];
			int newX = Vec[s].y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
			Q[newY][newX].push_front(1);
		}
	}
	Vec.clear();
}
// �ܿ￡�� tmpBoard�� ��и�ŭ ����� ä���ָ� ����� üũ..
void winter() {
	result = 0;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] += tmpBoard[hang][yal];
			result += Q[hang][yal].size();
		}
	}
}