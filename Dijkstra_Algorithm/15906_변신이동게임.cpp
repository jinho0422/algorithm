/*
	N*N ũ���� 2���� ������ ���� �������ִ� ĳ���͸� �����ؼ� ��ǥ �������� �̵���Ű�� Ŭ����Ǵ� �����̴�
	ĳ���ʹ� �Ϲ� ���� ���Ÿ�� 2�������ִ�. 
	�Ϲ� ����� ���� ĳ���ʹ� �� �Ͽ� �����¿� �߿��� �� �������� ��ĭ ������ �� �ִ�.
	���� ����� ���� �� �Ͽ� ĳ������ ���� ĭ�� �������� �����¿� �� �� ���⿡ �ִ� ���� ����� ���� �������� �̵��� ���� �ִ�.
	���� Ư�� ���⿡ ���� ������ �������� �ʴ´ٸ� �� �������δ� ������ �� ����.
	�Ϲݸ�忡�� ���Ÿ�尡 �Ǵµ����� t���� ���� �Ҹ�Ǹ�, ���� ��忡���� �Ϲݸ��� ���ư��µ����� ���� �Ҹ���� �ʴ´�.
	������ Ŭ�����ϴµ� �ʿ��� �ּ� �� ���� ���ϴ� �˰����� �����غ���.

	�Ϲݸ��� ���Ÿ�尡 �ְ� �Ϲݸ��� ���Ÿ���� ��ȭ�� ���ؼ� ��� ���� ������ �湮�� ���� �ִٰ� �����߰�,
	���������� ��ǥ���������� �ּ� �� ���� ���ϴ� �����̹Ƿ� ���ͽ�Ʈ�� �˰����� �����ߴ�.
*/


#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N, t, r, c;
char str[502];
char board[502][502];
int dij_board[2][502][502]; // 1���� - �Ϲ�/����, 2���� - ��, 3���� - ��
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, 1,  0, -1 };
int result;

typedef struct _pos {
	int h, y, T;
	bool flag; // flag == false �϶��� �Ϲݸ��, flag == true�϶��� ���Ÿ��
}pos;

struct cmp { // priority_queue�� ��뿡�� �ּ� �ϼ����� �����̱� ���� ����
	bool operator() (pos p, pos q) {
		return p.T > q.T;
	}
};
priority_queue < pos, vector<pos>, cmp> Q;

vector<int> Vec[1001]; // ��Ȧ�� ��ġ�� �־��ֱ� ���� ���� ..

void solve(int hang, int yal);

int main() {
	scanf("%d %d %d %d", &N, &t, &r, &c);
	for (int i = 0; i < 2; i++) { // ���ͽ�Ʈ�󿡼� dij_board[0][1][1]�� �����ϰ� INF�� ������ش�.
		for (int hang = 1; hang <= N; hang++) {
			for (int yal = 1; yal <= N; yal++) {
				if (i == 0 && hang == 1 && yal == 1) continue;
				dij_board[i][hang][yal] = INF;
			}
		}
	}

	for (int hang = 1; hang <= N; hang++) {
		scanf("%s", str);
		for (int yal = 1; yal <= N; yal++) {
			board[hang][yal] = str[yal - 1];
			if (board[hang][yal] == '#') { // ���� ��Ȧ�̸� ���� 1~500������ ���� ���� �־��ְ� 501~ 1000������ ���� ���� �־��ش�.
				Vec[hang].push_back(yal);
				Vec[500 + yal].push_back(hang);
			}
		}
	}

	for (int i = 1; i <= 1001; i++) { // ������ ��ġ���� �����¿� �������� ���� ����� ������ ã�� ���� ���͸� �������ش�.
		if (Vec[i].size() != 0) {
			sort(Vec[i].begin(), Vec[i].end());
		}
	}

	solve(1, 1);
	if (dij_board[0][r][c] >= dij_board[1][r][c]) result = dij_board[1][r][c];
	else result = dij_board[0][r][c];
	printf("%d\n", result);

	return 0;
}

void solve(int hang, int yal) {
	Q.push(pos({ hang, yal, 0, false }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (!p.flag) { // �Ϲݸ���϶��� �����¿츦 ���캸��
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

				if (dij_board[p.flag][newY][newX] > p.T + 1) { // �湮�� ���� ������ġ���� ���� �ϼ����� ũ�� �ϼ��� �ٲ��ְ� �̵�
					dij_board[p.flag][newY][newX] = p.T + 1;
					Q.push(pos({ newY, newX, dij_board[p.flag][newY][newX], p.flag }));
				}
			}
			if (dij_board[1][p.h][p.y] > p.T + t) { // �Ϲݸ���̸� �� �ڸ����� �Ϲݸ�忡�� ���Ÿ��� ��ȯ..
				dij_board[1][p.h][p.y] = p.T + t;
				Q.push(pos({ p.h, p.y, dij_board[1][p.h][p.y], true }));
			}
		}

		else { //���Ÿ���� ��..
			for (int dir = 0; dir < 4; dir++) {

				if (dir == 2) { // '��'���⿡�� ���� ���� ���������� ã�� ��
					if (Vec[500 + p.y].size() != 0) {
						for (int s = 0; s < Vec[500 + p.y].size(); s++) {
							int cnt = p.h - Vec[500 + p.y][s];
							if (cnt < 0) {// �ڽ��� ��ġ�� �����Ǿ������Ƿ� �ڽ��� ��ġ���� ���ĵ� ���͸� �ϳ��� �����鼭 cnt ���� -�� ������ '��'���⿡�� ���� ����� ��Ȧ�̴�.
								if (dij_board[1][Vec[500 + p.y][s]][p.y] > p.T + 1) { // ���Ÿ��� ��Ȧ�� ���� �� �湮�� �� �ִ��� �Ǵ�..
									dij_board[1][Vec[500 + p.y][s]][p.y] = p.T + 1;
									Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[1][Vec[500 + p.y][s]][p.y], true }));

									if (dij_board[0][Vec[500 + p.y][s]][p.y] > p.T + 1) {// ��Ȧ�� ������ ���� ���Ÿ���̹Ƿ� �Ϲݸ��� �ٲ� �� �ִ��� Ȯ���Ǵ�..
										dij_board[0][Vec[500 + p.y][s]][p.y] = p.T + 1;
										Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[0][Vec[500 + p.y][s]][p.y], false }));
									}
								}
								break;// ���� ����� ��Ȧ�� ã�����Ƿ� �������� �����ʱ����� break
							}
						}
					}
				}
				if (dir == 0) { // '��'����ó�� ������� ����� ��� ���ĵ� �迭�� �� �ں��� ���ָ鼭 +���� ������ ���� ���� ����� �����̴�.
					if (Vec[500 + p.y].size() != 0) {
						for (int s = Vec[500 + p.y].size() - 1; s >= 0; s--) {
							int cnt = p.h - Vec[500 + p.y][s];
							if (cnt > 0) {
								if (dij_board[1][Vec[500 + p.y][s]][p.y] > p.T + 1) {
									dij_board[1][Vec[500 + p.y][s]][p.y] = p.T + 1;
									Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[1][Vec[500 + p.y][s]][p.y], true }));

									if (dij_board[0][Vec[500 + p.y][s]][p.y] > p.T + 1) {
										dij_board[0][Vec[500 + p.y][s]][p.y] = p.T + 1;
										Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[0][Vec[500 + p.y][s]][p.y], false }));
									}
								}
								break;
							}
						}
					}
				}

				if (dir == 3) {
					if (Vec[p.h].size() != 0) {
						for (int s = Vec[p.h].size() - 1; s >= 0; s--) {
							int cnt = p.y - Vec[p.h][s];
							if (cnt > 0) {
								if (dij_board[1][p.h][Vec[p.h][s]] > p.T + 1) {
									dij_board[1][p.h][Vec[p.h][s]] = p.T + 1;
									Q.push(pos({ p.h, Vec[p.h][s], dij_board[1][p.h][Vec[p.h][s]], true }));

									if (dij_board[0][p.h][Vec[p.h][s]] > p.T + 1) {
										dij_board[0][p.h][Vec[p.h][s]] = p.T + 1;
										Q.push(pos({ p.h, Vec[p.h][s], dij_board[0][p.h][Vec[p.h][s]], false }));
									}
								}
								break;
							}
						}
					}
				}

				if (dir == 1) {
					if (Vec[p.h].size() != 0) {
						for (int s = 0; s < Vec[p.h].size(); s++) {
							int cnt = p.y - Vec[p.h][s];
							if (cnt < 0) {
								if (dij_board[1][p.h][Vec[p.h][s]] > p.T + 1) {
									dij_board[1][p.h][Vec[p.h][s]] = p.T + 1;
									Q.push(pos({ p.h, Vec[p.h][s], dij_board[1][p.h][Vec[p.h][s]], true }));

									if (dij_board[0][p.h][Vec[p.h][s]] > p.T + 1) {
										dij_board[0][p.h][Vec[p.h][s]] = p.T + 1;
										Q.push(pos({ p.h, Vec[p.h][s], dij_board[0][p.h][Vec[p.h][s]], false }));
									}
								}
								break;
							}
						}
					}
				}
			}
		}
	}
}