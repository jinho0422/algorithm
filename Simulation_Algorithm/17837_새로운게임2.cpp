#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;

int N, M;
int board[14][14]; // ������ ������ �������� 0 : ���, 1 : ������, 2 : �Ķ���
int dirY[5] = {0, 0, 0, -1, 1 };
int dirX[5] = {0, 1, -1, 0, 0 };
int result;

typedef struct _pos {
	int h, y, d;
}pos;

deque<int> Q[14][14]; // ���� �࿭ ��ġ�� ���� ����� ���� ����.. 
vector<pos> Vec[10]; // ���� ��,��, ����ִ� vector

void white(int horse, int H, int Y, int nY, int nX);
void red(int horse, int H, int Y, int nY, int nX);

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a][b].push_back(i);
		Vec[i].push_back(pos({ a, b, c }));
	}
	result = 1; // �����
	while (1) {
		for (int i = 0; i < M; i++) {
			//���ߵ� ��
			int newY = Vec[i][0].h + dirY[Vec[i][0].d];
			int newX = Vec[i][0].y + dirX[Vec[i][0].d];
			//���ߵɰ��� �Ķ����̰ų� ��谪�� �����
			if (newY <= 0 || newY > N  || newX <= 0 || newX > N || board[newY][newX] == 2) {
				//������ �ٲ㼭
				if (Vec[i][0].d == 1 || Vec[i][0].d == 3) Vec[i][0].d++;
				else if (Vec[i][0].d == 2 || Vec[i][0].d == 4) Vec[i][0].d--;
				//���ߵ� ���� ����
				newY = Vec[i][0].h + dirY[Vec[i][0].d];
				newX = Vec[i][0].y + dirX[Vec[i][0].d];
				// �ٽ� �Ķ����̰ų� ��谪�̸� continue
				if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 2) continue;
				// ���
				else if (board[newY][newX] == 0) white(i,Vec[i][0].h, Vec[i][0].y, newY, newX);
				// ������
				else if (board[newY][newX] == 1) red(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			}
			//���
			else if (board[newY][newX] == 0) white(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			//������
			else if (board[newY][newX] == 1) red(i, Vec[i][0].h, Vec[i][0].y, newY, newX);
			//���� �ϳ��� �̵��ϸ鼭 �� ������ 4���̻�𿴴��� ���� ����� ���
			for (int hang = 1; hang <= N; hang++) {
				for (int yal = 1; yal <= N; yal++) {
					if (Q[hang][yal].size() >= 4) {
						printf("%d\n", result);
						return 0;
					}
				}
			}
		}
		result++;
		if (result > 1000) break;	
	}
	printf("-1\n");
	return 0;;
}

void white(int horse, int H, int Y, int nY, int nX) {
	bool flag = false;
	int sz = Q[H][Y].size();
	for (int s = 0; s < sz; s++) {
		int p = Q[H][Y].front();
		Q[H][Y].pop_front();
		if (p == horse) flag = true;
		// ���ϴ� ���� ��Ÿ���� �̵��� ĭ���� �� �̵�
		if (flag) {	
			Q[nY][nX].push_back(p);
			Vec[p][0].h = nY, Vec[p][0].y = nX;
		}
		// ���ϴ� ���� ������ ������ ���ν״´�.
		else Q[H][Y].push_back(p);	
	}
}
void red(int horse, int H, int Y, int nY, int nX) {
	bool flag = false;
	stack<int> S;
	int sz = Q[H][Y].size();
	for (int s = 0; s < sz; s++) {
		int p = Q[H][Y].front();
		Q[H][Y].pop_front();
		if (p == horse) flag = true;
		// ���ϴ� ���� ��Ÿ���� stack�� ����
		if (flag) {
			S.push(p);
		}
		//���ϴ� ���� ������ ������ ���� �״´�
		else Q[H][Y].push_back(p);
	}
	//������ �ֱ� ����..
	int Ssz = S.size();
	for (int i = 0; i < Ssz; i++) {
		int p = S.top();
		S.pop();
		Q[nY][nX].push_back(p);
		Vec[p][0].h = nY, Vec[p][0].y = nX;
	}
}
