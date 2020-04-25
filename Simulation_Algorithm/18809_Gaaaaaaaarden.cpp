/*
	https://www.acmicpc.net/problem/18809
	������ ���� �� �ִ� ���߿� Green + Red ������ �̴� DFS,
	DFS�� ���� ������ Green�� ���� �� Red�� ���� ���� ã�� DFS,
	ã�� ������ ���� GQ, RG�� �־� ���ÿ� ������ ���� BFS�� ã�� �˰��� ����.
*/



#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, M, G, R;
int board[50][50];
bool checkGreen[11]; // Green ������ ������ Red ������ ������ �Ǵ��ϴ� check.
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

int checkFlower[50][50]; // ���ÿ� ���� �� �ִ��� �Ǵ��ϴ� check.
bool Green[50][50]; // Green ������ �ְ� BFS ���� check
bool Red[50][50]; // Red ������ �ְ� BFS ���� check
int result;
int assume;

typedef struct _pos {
	int h, y;
}pos;
pos tmp[11];

vector<pos> Vec; // ������ ���� �� �ִ� ���� �ִ� vector
queue<pos> GQ; // Green������ ���� queue
queue<pos> RQ; // Red������ ���� Red

void solve_DFS(int depth, int start);

int main() {
	scanf("%d %d %d %d", &N, &M, &G, &R);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 2) Vec.push_back(pos({ hang, yal })); // board == 2 ������ ���� �� �ִ� ������ vector�� �־��ش�.
		}
	}
	solve_DFS(0, 0); // ������ ���� �� �ִ� �� �߿� Green, Red ��ü ������ ���� ���� ã�� DFS 
	printf("%d\n",result);
	return 0;
}

void BFS(int num) {
	assume = 0;
	while (!RQ.empty() || !GQ.empty()) {
		//Green ������ ���� �����鼭 
		int Gsz = GQ.size();
		for (int s = 0; s < Gsz; s++) {
			pos p = GQ.front();
			GQ.pop();
			if (Red[p.h][p.y]) continue; // �������� �������� ���� �� ���̸� continue..

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// board�� ȣ���� �ƴϰ�  Green, Red ��� �湮�� ���� ���� ���̸�..
				if (board[newY][newX] != 0 && !Green[newY][newX] && !Red[newY][newX] && checkFlower[newY][newX] == 0) {
					Green[newY][newX] = true;
					checkFlower[newY][newX] = num; // ��п� �湮�� ������ üũ�� �س��..
					GQ.push(pos({ newY, newX }));
				}
			}
		}
		// �� ��, Red ������ �����鼭
		int Rsz = RQ.size();
		for (int s = 0; s < Rsz; s++) {
			pos p = RQ.front();
			RQ.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == 0) continue;
				// ���� �ð��� �湮�� ���̸� assume��++�� ���־� ���� �ɰ��� �Ǵ�..
				if (board[newY][newX] != 0 && !Red[newY][newX]) {
					if (Green[newY][newX] && checkFlower[newY][newX] == num) {
						Red[newY][newX] = true;
						assume++;
					}
					//�ƴϸ� RQ�� �־��ش�..
					if (!Green[newY][newX] && checkFlower[newY][newX] != num) {
						Red[newY][newX] = true;
						RQ.push(pos({ newY, newX }));
					}
				}
			}
		}
		num++; // Green�� Red�� ��� ���� �ð��� �帧�� �־��ش�.
	}
	//����� ����..
	if (result < assume) result = assume;
}

void DFS(int depth, int start) {

	if (depth == G) {
		// Green���װ� Red������ checkGreen�� ���Ͽ� �и��Ͽ� �ִ´�.
		for (int s = 0; s < G + R; s++) {
			if (checkGreen[s]) {
				Green[tmp[s].h][tmp[s].y] = true;
				GQ.push(pos({ tmp[s].h, tmp[s].y }));
			}
			else {
				Red[tmp[s].h][tmp[s].y] = true;
				RQ.push(pos({ tmp[s].h, tmp[s].y }));
			}
		}
		BFS(1);
		// �ʱ�ȭ..
		memset(Green, false, sizeof(Green));
		memset(Red, false, sizeof(Red));
		memset(checkFlower, 0, sizeof(checkFlower));
		while (!RQ.empty()) RQ.pop();
		while (!GQ.empty()) GQ.pop();
		return;
	}

	for (int s = start; s < G + R; s++) {
		checkGreen[s] = true;
		DFS(depth + 1, s + 1);
		checkGreen[s] = false;
	}
}

void solve_DFS(int depth, int start) {
	if (depth == G + R) {
		DFS(0, 0); // Green, Red�� ���� board���� Green�� ��� ������ Red�� ��� ������ ã�� DFS
		return;
	}
	for (int s = start; s < Vec.size(); s++) {
		tmp[depth] = { Vec[s].h, Vec[s].y };
		solve_DFS(depth + 1, s + 1);
	}
}