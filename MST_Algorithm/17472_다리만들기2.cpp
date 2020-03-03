/*
	��� ���� �ٸ��� �����Ϸ��� ����� N*Mũ���̰� 1�� �κ��� ��, 0 �κκ��� �ٴ��̴�.
	�ٸ��� �ٸ� ������ ���� or ���ηθ� ���� �� �ִ�.(�߰��� ���� ������ �ȵǰ� �ٸ��� ���̰� 1�̿��� �ȵȴ�.)
	��� ���� �����ϴ� �ٸ� ������ �ּڰ��� ������.

	BFS�� �̿��Ͽ� ������ ���� ��ȣ�� �ű�� �� ���� ��ġ���� �ٸ� �������� �Ÿ���
	���Ϳ� �־� ���Ͽ����ε带�Ͽ� MST�� ����Ͽ���.
	*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int board[10][10];
bool check[10][10]; // ���� ��ȣ�� �ű������..
int parent[7]; // ���Ͽ� ���ε带 ����..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int num; // ���� ��ȣ
int result;

typedef struct _pos {// ���� ��ȣ�� �ű������ hang, yal�� Q�� �ֱ�����..
	int h, y;
}pos;

typedef struct _pos1 { // ������ ���ۼ��� ������ �� �ٸ��� ���̸� �ֱ�����..
	int A, B, W;
}pos1;

bool cmp(const pos1 p, const pos1 q) { // MST�� ����ϱ� ���ؼ��� ���� ������ �ʿ�..
	return p.W < q.W;
}

vector<pos1> Vec;

void BFS(int hang, int yal, int n);

int find_(int x) { // ���Ͽ����ε带 ����(�θ� ã������..)
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}


	num = 1;

	for (int hang = 0; hang < N; hang++) { // BFS�� �̿��� ���� ��ȣ �ű��..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal, num);
				num++;
			}
		}
	}

	for (int i = 1; i < num; i++) { // ���Ͽ� ���ε带 ���� parent�� �ڱ� �ڽ����� ����..
		parent[i] = i;
	}

	for (int hang = 0; hang < N; hang++) { // �ʿ��� ���̸� �ٴٰ� �ƴϸ�..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] != 0) {
				for (int dir = 0; dir < 4; dir++) { // �����¿�� ����
					int cnt = 0; int copy_hang = hang; int copy_yal = yal; // �ٸ��� ��Ʈ�������� �ʱⰪ.
					while (1) {
						int newY = copy_hang + dirY[dir];
						int newX = copy_yal + dirX[dir];
						if (newY < 0 || newY > N -1 || newX < 0 || newX > M -1 || board[hang][yal] == board[newY][newX]) break;
						// ����ũ�⸦ ����ų� ���� ���̸� �ѱ��..
						if (board[newY][newX] == 0) { // �ٴ��̸� �ٸ��� ũ�⸦ ������Ű�� ���� �������� ������ ���� hang, yal�� ���� �ٲ��ش�.
							copy_hang = newY; copy_yal = newX; cnt++;
						}
						if (board[newY][newX] != 0 && board[newY][newX] != board[hang][yal]) { // �ٴٰ� �ƴϰ� �ϳ��� ������ �ٸ� ���� �����ϴ� ���
							if (cnt == 1) break; // �ٸ��� ũ�Ⱑ 1�̸� �������´�..
							Vec.push_back(pos1({ board[hang][yal], board[newY][newX], cnt })); // �ٸ��� ũ�Ⱑ 1�� �ƴϸ� ���Ϳ� �ִ´�.
							break;
						}
					}
				}
			}
		}
	}

	sort(Vec.begin(), Vec.end(), cmp); // MST�� ����ϱ� ���� ����..

	int sz = Vec.size();
	int area_num = 1; // ��� ���� �� ���������� ���� ���� �ʱⰪ.
	bool flag = false;

	for (int s = 0; s < sz; s++) { // ���Ͽ����ε�...
		int a_head = find_(Vec[s].A);
		int b_head = find_(Vec[s].B);

		if (a_head != b_head) {// �θ��� ���� �ٸ��� ���Ͽ�..
			parent[a_head] = b_head;
			result += Vec[s].W; // �ٸ��� ���̸� �����ش�..
			area_num++; // ����� ���� ������ üũ
			if (area_num == num - 1) flag = true; // ��� ���� ����Ǹ� flag true
		}
	}
	if (flag) printf("%d\n", result);
	else printf("-1\n");

	return 0;
}

void BFS(int hang, int yal, int n) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	board[hang][yal] = n;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = n;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}