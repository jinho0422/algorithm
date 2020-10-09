#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;
int board[21][21];
int check[21][21]; // ������ �� �ִ� �� üũ..
int shark[21][21]; // �� �ִ°� üũ..
int dirY[5] = { 0, -1, 1, 0, 0 };// 1.�� 2.�Ʒ� 3.���� 4.������
int dirX[5] = { 0, 0, 0, -1, 1 };
int pri[401][5][4];
int result, kill;
bool resultFlag;

typedef struct _pos {
	int h, y, d;
	bool flag;
}pos;
vector<pos> Vec[401];
queue<int> Q[21][21];

void move();

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] != 0) {
				Vec[board[hang][yal]].push_back(pos({ hang, yal, 0, false }));
				check[hang][yal] = K;
				shark[hang][yal] = board[hang][yal];
			}
		}
	}
	kill = M; // ����� ���� (������ kill--)
	//ó�� �켱���� ����
	for (int a, i = 1; i <= M; i++) {
		scanf("%d", &a);
		Vec[i][0].d = a;
	}
	// ������ ���� ������ �켱���� ����
	for (int a, i = 1; i <= M; i++) {
		for (int j = 1; j < 5; j++) {
			for (int u = 0; u < 4; u++) {
				scanf("%d", &a);
				pri[i][j][u] = a;
			}
		}
	}
	while (1) {
		move();
		result++;
		if (result > 1000) {
			resultFlag = true;
			break;
		}
		if (kill == 1) break;
	}
	if (!resultFlag) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}

void move() {
	//����̵�
	for (int i = 1; i <= M; i++) {
		if (Vec[i][0].flag) continue; // ���� ���� ������
		bool flag = false;
		for (int dir = 0; dir < 4; dir++) {
			int newY = Vec[i][0].h + dirY[pri[i][Vec[i][0].d][dir]];
			int newX = Vec[i][0].y + dirX[pri[i][Vec[i][0].d][dir]];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
			//������ �� �ִ°�
			if (check[newY][newX] == 0) {
				flag = true;
				Vec[i][0].h = newY, Vec[i][0].y = newX, Vec[i][0].d = pri[i][Vec[i][0].d][dir];
				Q[newY][newX].push(i);
				break;
			}
		}
		if (!flag) {
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[i][0].h + dirY[pri[i][Vec[i][0].d][dir]];
				int newX = Vec[i][0].y + dirX[pri[i][Vec[i][0].d][dir]];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;

				if (shark[newY][newX] == i) {
					flag = true;	
					Vec[i][0].h = newY, Vec[i][0].y = newX, Vec[i][0].d = pri[i][Vec[i][0].d][dir];
					Q[newY][newX].push(i);
					break;
				}
			}
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (Q[hang][yal].size() > 1) {
				int sz = Q[hang][yal].size();
				for (int s = 0; s < sz; s++) {
					if (s == 0) {
						int p = Q[hang][yal].front();
						shark[hang][yal] = p;
						check[hang][yal] = K;
						Q[hang][yal].pop();
					}
					else {
						int p = Q[hang][yal].front();
						Vec[p][0].flag = true;
						kill--;
						Q[hang][yal].pop();
					}
				}
			}
			else if (Q[hang][yal].size() == 1) {
				int p = Q[hang][yal].front();
				shark[hang][yal] = p;
				check[hang][yal] = K;
				Q[hang][yal].pop();
			}
		}
	}
	//���� ���ֱ�..
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (shark[hang][yal] == 0) continue;
			if (check[hang][yal] > 0) {
				if (Vec[shark[hang][yal]][0].h == hang && Vec[shark[hang][yal]][0].y == yal && !Vec[shark[hang][yal]][0].flag) continue;
				check[hang][yal]--;
				if (check[hang][yal] == 0) {		
					shark[hang][yal] = 0;
				}		
			}
		}
	}
}