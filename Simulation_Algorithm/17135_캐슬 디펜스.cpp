#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, D;
int board[15][15];
int tmpBoard[15][15]; // ���� �ü��� �ְ� board�� ���͸� ī���ϱ� ����..
int atacker[3]; // ���� ��� �ü��� ������..
int die[3]; // ���ϴ� ���� ������ �ѹ��� �ִ� �迭
bool check[15];
int result; // �����
int tmpNum; // ������ ���� ī���ϱ�����..

typedef struct _pos {
	int h, y; // h : hang, y : yal, flag : ���Ͱ� �׾����� ��Ҵ���
	bool flag;
}pos;
pos monster[225]; // ������ hang, yal�� �ִ´�.
int num = 0; // ������ ��

bool cmp (const pos& p, const pos& q) { // hang�� ū�ź����ϸ鼭 hang�� ���� ��� yal�� �����ź���
	if (p.y == q.y) return p.h > q.h;
	return p.y < q.y;
}

vector<pos> Vec;

void DFS(int depth, int start);

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &D);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) monster[num++] = { hang, yal, false }; // ���� ����
		}
	}
	DFS(0, 0);
	//���
	printf("%d\n", result);
	return 0;
}

int solve() {
	int cnt = 0; // ���� ���� ��

	while (1) {
		for (int i = 0; i < 3; i++) die[i] = -1; // ���� ������ ��ȣ�� �ֱ�..
		// �ü��� ���͸� ��� ���鼭 ���� �����鼭 ���ʿ� ��ġ�� ���̸� ã�´�.
		for (int i = 0; i < 3; i++) {
			int sh = N, sy = atacker[i]; // �ü��� ��ġ
			int minDir = 987654321; // �ü��� ���� �ּҰŸ��� ���͸� ã������
			for (int j = 0; j < Vec.size(); j++) {
				if (Vec[j].flag) continue; // �װų� ������ ���ʹ� continue..
				int dir = abs(sh - Vec[j].h) + abs(sy - Vec[j].y); // �ü��� ������ �Ÿ�
				if (dir <= D) { // ȭ���� �ݴ°��϶�
					if (minDir > dir) { // ���� ������
						minDir = dir;
						die[i] = j; // ���� �����ǹ�ȣ�� ����..
					}
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if (die[i] == -1) continue; // �ü��� �ƹ��� ���׿��� ���
			if (!Vec[die[i]].flag) { // ���� ���� �����̸�
				Vec[die[i]].flag = true;
				cnt++; // ���δ�..
				tmpNum--;// ���Ͱ���--;
				if (tmpNum == 0) return cnt; // ���Ͱ� ��� �������� �� return cnt;;
			}
		}
		// ���͸� ��� �Ʒ��� ��ĭ �����ش�..
		for (int i = 0; i < Vec.size(); i++) {
			if (Vec[i].flag) continue; // ���� ���ʹ� ������ ���ΰ�
			Vec[i].h++; // �Ʒ��� ��ĭ ������ ���� �ñ��� �����ϸ� �������� �����..
			if (Vec[i].h == N) {
				Vec[i].flag = true;
				tmpNum--;
				if (tmpNum == 0) return cnt;
 			}
		}	
	}
}

void DFS(int depth, int start) {
	if (depth == 3) {
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // ���� ī��..
		//�ʱ�ȭ
		Vec.clear();
		tmpNum = num;
		// ���͸� vector�� ��� sort..
		for (int i = 0; i < num; i++) Vec.push_back(pos({ monster[i].h, monster[i].y, false }));	
		sort(Vec.begin(), Vec.end(), cmp);
		int sum = solve();
		// ����� ����
		if (result < sum) result = sum;
		return;
	}
	// �ü��� ���� ���� ��ġ�� atacker�迭�� �ִ´�..
	for (int i = start; i < M; i++) {
		if (!check[i]) {
			check[i] = true;
			atacker[depth] = i;
			DFS(depth + 1, i + 1);
			atacker[depth] = 0;
			check[i] = false;
		}
	}
}