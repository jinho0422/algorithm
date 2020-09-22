#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int N, K;
char str[51];
int board[51][51];
bool check[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int parent[266];
int result;
bool flag;

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : �ϳ��� ���迡�� �ٸ� ����� ���� �ð�
}pos;
queue<pos> Q;

typedef struct _pos1 {
	int A, B, W; // A : ���� A, B : ���� B , W : A���� B�� ���� �ð�
}pos1;
bool cmp(const pos1& p, const pos1& q) {
	return p.W < q.W;
};
vector<pos1> Vec;

void BFS(int hang, int yal);
int find_(int x) {
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	int names = 2;
	//�Է�
	scanf("%d %d", &N, &K);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] -'0';
			//������ �Ǵ� ���� �˾Ƴ��� ���� 0, 1�� �ƴ� 2���� �����Ѵ�..
			if (board[hang][yal] == 'S' - '0') board[hang][yal] = names++;
			else if (board[hang][yal] == 'K' - '0') board[hang][yal] = names++;
		}
	}
	// ������ �������� �ٸ� �������� �̵��� �ð��� vector�� �ִ´�..
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			if (board[hang][yal] > 1) {
				BFS(hang, yal);
				memset(check, false, sizeof(check));
			}
		}
	}
	//MST�� ����Ͽ� ������ �湮�ϴ� �ִܰŸ��� ���Ѵ�..
	for (int i = 0; i < 260; i++) parent[i] = i;
	sort(Vec.begin(), Vec.end(), cmp);
	int cnt = 0;
	for (int s = 0; s < Vec.size(); s++) {
		int headA = find_(Vec[s].A);
		int headB = find_(Vec[s].B);

		if (headA != headB) {
			parent[headA] = headB;
			result += Vec[s].W;
			cnt++;
			if (cnt == K) {
				flag = true;
				break;
			}
		}
	}
	//���
	if (flag) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) continue;

			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX, p.cnt + 1 }));
			}
			if (board[newY][newX] != 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				Vec.push_back(pos1({ board[hang][yal], board[newY][newX], p.cnt + 1 }));
			}
		}
	}
}