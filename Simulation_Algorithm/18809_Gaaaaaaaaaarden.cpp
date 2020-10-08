#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M, G, R;
int board[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool check[10]; // ����� �� �մ� ���� ����� �� �׸��� ������ ���带 ������ �Ǵ�..
int checkG[51][51]; // �׸� ������ ��п� �ɾ����� �ľ��ϴ� �迭
int checkR[51][51]; // ���� ������ ��п� �ɾ����� �ľ��ϴ� �迭
bool checkMade[51][51]; // ���� �ð��� �׸�, ���� ������ ���� ���� �� ��츦 �Ǵ�..
int time, made, result; // time : ������ ������ �̵��� �ð�, made : ���� �� ��� ���� : result : ���� �����

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec; // ����� �� �ִ� ���..
pos seed[11];

queue<pos> Gr; // �׸� ����
queue<pos> Re; // ���� ����

void DFS(int depth, int start);

int main() {
	//�Է�
	scanf("%d %d %d %d", &N, &M, &G, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal })); // ������ ���� �� �ִ� ���̸� Vec�� �ִ´�
		}
	}
	DFS(0, 0);
	//���
	printf("%d\n", result);
	return 0;
}

void BFS() {
	time = 2; // ������ �̵��� �ð�..
	while (!Gr.empty() || !Re.empty()) {
		int Gsz = Gr.size();
		for (int s = 0; s < Gsz; s++) {
			pos p = Gr.front();
			Gr.pop();

			if (checkMade[p.h][p.y]) continue; // ���� ������� ���� continue..

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// �׸�, ���� ������ ��� �Ƚɾ��������� �׸� ���� ���� �̵�..
				if (checkG[newY][newX] == 0 && checkR[newY][newX] == 0) {
					checkG[newY][newX] = time;
					Gr.push(pos({ newY, newX }));
				}
			}
		}
		int Rsz = Re.size();
		for (int s = 0; s < Rsz; s++) {
			pos p = Re.front();
			Re.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// ������׵� �����ʰ� �׸� ���׵� ���� ���� ������ �̵�
				if (checkR[newY][newX] == 0 && checkG[newY][newX] == 0) {
					checkR[newY][newX] = time;
					Re.push(pos({ newY, newX }));
				}
				//���� ��������� ���� �ʾ�� �׸� ������ ���� �ð��� ���� ���̶�� checkMade : true
				if (checkR[newY][newX] == 0 && checkG[newY][newX] == time) {
					checkMade[newY][newX] = true;
				}
			}
		}
		time++;
	}
}
// �̾Ƴ� ������ ���� �� �ִ� ���߿� ���带 �������� �׸��� ���� ���� check�� �Ǵ��Ѵ�..
void DFS1(int depth, int start) {
	if (depth == G) {
		//�ʱ�ȭ
		memset(checkR, 0, sizeof(checkR));
		memset(checkG, 0, sizeof(checkG));
		memset(checkMade, false, sizeof(checkMade));
		while (!Gr.empty()) Gr.pop();
		while (!Re.empty()) Re.pop();
		// check[i] : �׸� ������ ������ !check[i] : ���� ������ ���� ��
		for (int i = 0; i < G + R; i++) {
			if (check[i]) {
				checkG[seed[i].h][seed[i].y] = 1;
				Gr.push(pos({ seed[i].h, seed[i].y }));
			}
			else {
				checkR[seed[i].h][seed[i].y] = 1;
				Re.push(pos({ seed[i].h, seed[i].y }));
			}
		}
		BFS();
		// ���� ������� �� ����
		made = 0;
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (checkMade[hang][yal]) made++;
			}
		}
		//����
		if (result < made) result = made;
		return;
	}
	for (int s = start; s < G + R; s++) {
		check[s] = true;
		DFS1(depth + 1, s + 1);
		check[s] = false;
	}
}
// ������ ���� �� �ִ� ���߿� R + G ����ŭ �̾� ����..(����)
void DFS(int depth, int start) {
	if (depth == G + R) {
		DFS1(0, 0);
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		seed[depth] = { Vec[s].h, Vec[s].y };
		DFS(depth + 1, s + 1);
		seed[depth] = { 0, 0 };
	}
}