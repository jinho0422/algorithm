#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int board[21][21];
bool check[21][21];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int fish;
int result;

//����� H, Y == ��ġ��, size = ũ��, cnt = ����⸦ � �Ծ����� �Ǵ��� ���� struct
typedef struct _pos1 {
	int H, Y, size, cnt;
}pos1;
// ����⸦ ���� ��ġ�� �� �����̴� ��ġ�� �Ǵ��ϱ� ���� struct
typedef struct _pos {
	int h, y;
}pos;

//������ �Ÿ����� ����� ��ġ�� ������ ���ʺ��� �Ʒ��� �����ʱ��� �����ϴ� struct
bool cmp(const pos& p, const pos& q) {
	if (p.h == q.h) return p.y < q.y;
	return p.h < q.h;
}

pos1 shark[1]; // ����� ����
vector<pos> Vec; // ������ �� ���� ������� ����
queue<pos> Q; // ����� ������ ����

void BFS(int hang, int yal);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] >= 1 && board[hang][yal] <= 6) fish++; // ������� ���� üũ..
			if (board[hang][yal] == 9) shark[0] = { hang, yal, 2, 0 }; // ����� ���� �Է�
		}
	}
	//����Ⱑ �Ѹ����� ������ ���
	if (fish == 0) {
		printf("%d\n", result);
		return 0;
	}
	BFS(shark[0].H, shark[0].Y);
	printf("%d\n", result);

	return 0;
}

void BFS(int hang, int yal) {
	// ������ ����� ��ġ üũ
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int movecnt = 0; // ������ Ƚ��
	while (!Q.empty()) {
		int sz = Q.size();
		// queue�� ����ִ¸�ŭ�� �����̸鼭
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// ����� ũ��� ���ų� ���� �� �� Ȯ���� ĭ�� �ƴ϶��
				if (board[newY][newX] <= shark[0].size && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					// ���� ������� ũ�Ⱑ ����� ũ�⺸�� �۰ų� ����Ⱑ ���� ���� �ƴ϶�� ����� ��ġ ����
					if (board[newY][newX] > 0 && board[newY][newX] < shark[0].size) {
						Vec.push_back(pos({ newY, newX }));
					}
				}
			}
		}
		movecnt++; // ��� �̵�Ƚ�� ����
		// ����Ⱑ �� ���� ���� �ִٸ�
		if (Vec.size() != 0) {
			shark[0].cnt++; // �� ����⸦ ���� Ƚ�� ����
			if (shark[0].cnt == shark[0].size) { // ���� ����� ũ��� ����� ���� Ƚ���� ���ٸ� ���� Ƚ�� �ʱ�ȭ ����� ũ�� ����
				shark[0].cnt = 0;
				shark[0].size++;
			}
			// ����⸦ ���� �� �� ������ ���ʺ��� �Ʒ����� �����ʱ��� ����..
			sort(Vec.begin(), Vec.end(), cmp);
			// �������ġ �̵�
			board[hang][yal] = 0;
			board[Vec[0].h][Vec[0].y] = 9;
			// ������� ������ ����..
			result += movecnt;
			movecnt = 0;
			// �ʱ�ȭ
			while (!Q.empty()) Q.pop();
			memset(check, false, sizeof(check));
			// ����� ��ġ�� �ٽ� �ֱ�
			Q.push(pos({ Vec[0].h, Vec[0].y }));
			check[Vec[0].h][Vec[0].y] = true;
			hang = Vec[0].h, yal = Vec[0].y; // ����� ��ġ �ʱ�ȭ..
			Vec.clear(); // �Ծ��� ����� �ʱ�ȭ..
		}
	}
}