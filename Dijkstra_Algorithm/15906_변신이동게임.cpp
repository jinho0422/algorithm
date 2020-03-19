/*
	N*N 크기의 2차원 격자의 시작 지점에있는 캐릭터를 조작해서 목표 지점까지 이동시키면 클리어되는 게임이다
	캐릭터는 일반 모드와 변신모드 2가지가있다. 
	일반 모드일 때는 캐릭터는 한 턴에 상하좌우 중에서 한 방향으로 한칸 움직일 수 있다.
	변신 모드일 때는 한 턴에 캐릭터의 현재 칸을 기준으로 상하좌우 중 한 방향에 있는 가장 가까운 워프 지점으로 이동할 수만 있다.
	만약 특정 방향에 워프 지점이 존재하지 않는다면 그 방향으로는 움직일 수 없다.
	일반모드에서 변신모드가 되는데에는 t개의 턴이 소모되며, 변신 모드에서는 일반모드로 돌아가는데에는 턴이 소모되지 않는다.
	게임을 클리어하는데 필요한 최소 턴 수를 구하는 알고리즘을 구현해보자.

	일반모드와 변신모드가 있고 일반모드와 변신모드의 변화를 통해서 행과 열을 여러번 방문할 수도 있다고 생각했고,
	한지점에서 목표지점까지의 최소 턴 수를 구하는 문제이므로 다익스트라 알고리즘을 선택했다.
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
int dij_board[2][502][502]; // 1차원 - 일반/변신, 2차원 - 햄, 3차원 - 열
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, 1,  0, -1 };
int result;

typedef struct _pos {
	int h, y, T;
	bool flag; // flag == false 일때는 일반모드, flag == true일때는 변신모드
}pos;

struct cmp { // priority_queue의 사용에서 최소 턴수부터 움직이기 위한 정렬
	bool operator() (pos p, pos q) {
		return p.T > q.T;
	}
};
priority_queue < pos, vector<pos>, cmp> Q;

vector<int> Vec[1001]; // 웜홀의 위치를 넣어주기 위한 백터 ..

void solve(int hang, int yal);

int main() {
	scanf("%d %d %d %d", &N, &t, &r, &c);
	for (int i = 0; i < 2; i++) { // 다익스트라에서 dij_board[0][1][1]를 제외하고 INF로 만들어준다.
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
			if (board[hang][yal] == '#') { // 만약 웜홀이면 백터 1~500까지는 햄의 열을 넣어주고 501~ 1000까지는 열의 행을 넣어준다.
				Vec[hang].push_back(yal);
				Vec[500 + yal].push_back(hang);
			}
		}
	}

	for (int i = 1; i <= 1001; i++) { // 현재의 위치에서 상하좌우 각각에서 가장 가까운 지점을 찾기 위해 백터를 정렬해준다.
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

		if (!p.flag) { // 일반모드일때는 상하좌우를 살펴보고
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

				if (dij_board[p.flag][newY][newX] > p.T + 1) { // 방문한 곳이 현재위치에서 가는 턴수보다 크면 턴수를 바꿔주고 이동
					dij_board[p.flag][newY][newX] = p.T + 1;
					Q.push(pos({ newY, newX, dij_board[p.flag][newY][newX], p.flag }));
				}
			}
			if (dij_board[1][p.h][p.y] > p.T + t) { // 일반모드이면 그 자리에서 일반모드에서 변신모드로 변환..
				dij_board[1][p.h][p.y] = p.T + t;
				Q.push(pos({ p.h, p.y, dij_board[1][p.h][p.y], true }));
			}
		}

		else { //변신모드일 때..
			for (int dir = 0; dir < 4; dir++) {

				if (dir == 2) { // '하'방향에서 가장 작은 워프지점을 찾을 때
					if (Vec[500 + p.y].size() != 0) {
						for (int s = 0; s < Vec[500 + p.y].size(); s++) {
							int cnt = p.h - Vec[500 + p.y][s];
							if (cnt < 0) {// 자신의 위치는 고정되어있으므로 자신의 위치에서 정렬된 백터를 하나씩 빼보면서 cnt 값이 -가 나오면 '하'방향에서 가장 가까운 웜홀이다.
								if (dij_board[1][Vec[500 + p.y][s]][p.y] > p.T + 1) { // 변신모드로 웜홀에 왔을 때 방문할 수 있는지 판단..
									dij_board[1][Vec[500 + p.y][s]][p.y] = p.T + 1;
									Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[1][Vec[500 + p.y][s]][p.y], true }));

									if (dij_board[0][Vec[500 + p.y][s]][p.y] > p.T + 1) {// 웜홀에 들어왔을 때는 변신모드이므로 일반모드로 바꿀 수 있는지 확인판단..
										dij_board[0][Vec[500 + p.y][s]][p.y] = p.T + 1;
										Q.push(pos({ Vec[500 + p.y][s], p.y, dij_board[0][Vec[500 + p.y][s]][p.y], false }));
									}
								}
								break;// 가장 가까운 웜홀을 찾앗으므로 나머지는 보지않기위해 break
							}
						}
					}
				}
				if (dir == 0) { // '하'방향처럼 상방향을 해줬다 대신 정렬된 배열의 맨 뒤부터 빼주면서 +값이 나오는 곳이 가장 가까운 방향이다.
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