#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, C;
int board[102][102];
int dirY[5] = { 0, -1, 1, 0, 0 };
int dirX[5] = { 0, 0, 0, 1, -1 }; // ��, �Ʒ�, ������, ����
int result;

typedef struct _pos {
	int h, y, v, dr, w; // h : hang, y : yal, v : �ӵ�, dr : ����, w : ũ��
	bool flag;
}pos;
vector<pos> Vec[100001];

typedef struct _pos1 {
	int n, big; // n : ����� ��ȣ, big : ����� ũ��
}pos1;
struct cmp {
	bool operator() (pos1 p, pos1 q) {
		return p.big < q.big;
	}
};
priority_queue<pos1, vector<pos1>, cmp> Q[101][101];

void search(int yal);
void move();

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &C);
	for (int r, c, s, d, z, i = 1; i <= C; i++) {
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		board[r][c] = i;
		Vec[i].push_back(pos({ r, c, s, d, z }));
	}
	for (int yal = 1; yal <= M; yal++) {
		//����� ���� �ű�鼭 �� ��� �Լ�
		search(yal);
		// �� �����δ�..
		move();
	}
	printf("%d\n", result);
	return 0;
}

void search(int yal) {
	for (int hang = 1; hang <= N; hang++) {
		if (board[hang][yal] != 0) {
			Vec[board[hang][yal]][0].flag = true;
			result += Vec[board[hang][yal]][0].w;
			return;
		}
	}
}
void move() {
	memset(board, 0, sizeof(board));
	for (int i = 1; i <= C; i++) {
		if (Vec[i][0].flag) continue; // ������ ���� continue..
		int first = 0;
		 //���Ͽ�����..
		if (Vec[i][0].dr == 1 || Vec[i][0].dr == 2) {
			first = Vec[i][0].v % ((N - 1) * 2); // �ӵ��� ������������ �����δ�.
			int sh = Vec[i][0].h, sy = Vec[i][0].y;
			for (int j = 0; j < first;) {
				int newY = sh + dirY[Vec[i][0].dr];
				int newX = sy + dirX[Vec[i][0].dr];

				if (newY <= 0 || newY > N) {
					if (Vec[i][0].dr == 1) Vec[i][0].dr += 1; //���οö� �� ������ �Ʒ��� �ٲٱ�..
					else Vec[i][0].dr -= 1; // �Ʒ��γ������� ���� ����ٲٱ�..
					continue;
				}
				sh = newY, sy = newX;
				j++;
			}
			Vec[i][0].h = sh, Vec[i][0].y = sy;
			Q[sh][sy].push(pos1({ i, Vec[i][0].w }));
		}
		//�¿������..
		else if (Vec[i][0].dr == 3 || Vec[i][0].dr == 4) {
			first = Vec[i][0].v % ((M - 1) * 2);
			int sh = Vec[i][0].h, sy = Vec[i][0].y;
			for (int j = 0; j < first;) {
				int newY = sh + dirY[Vec[i][0].dr];
				int newX = sy + dirX[Vec[i][0].dr];

				if (newX <= 0 || newX > M) {
					if (Vec[i][0].dr == 3) Vec[i][0].dr += 1; // ��ΰ������� �� �·� ����ٲٱ�
					else Vec[i][0].dr -= 1; // �·ΰ������� �� ��� ����ٲٱ�..
					continue;
				}
				sh = newY, sy = newX;
				j++;
			}
			Vec[i][0].h = sh, Vec[i][0].y = sy;
			Q[sh][sy].push(pos1({ i, Vec[i][0].w })); // ��� �����̰� ���̱�..
		}
	}
	// ���λ���� ���� ũ�Ⱑ ū �� ���ΰ� �������� ���δ�..
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			if (Q[hang][yal].size() == 0) continue;
			pos1 p = Q[hang][yal].top();
			board[Vec[p.n][0].h][Vec[p.n][0].y] = p.n;
			Q[hang][yal].pop();
			while (!Q[hang][yal].empty()) {
				p = Q[hang][yal].top();
				Vec[p.n][0].flag = true;
				Q[hang][yal].pop();
			}
		}
	}
}