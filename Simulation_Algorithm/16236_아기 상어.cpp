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

//상어의 H, Y == 위치와, size = 크기, cnt = 물고기를 몇개 먹었는지 판단을 위한 struct
typedef struct _pos1 {
	int H, Y, size, cnt;
}pos1;
// 물고기를 먹은 위치와 상어가 움직이는 위치를 판단하기 위한 struct
typedef struct _pos {
	int h, y;
}pos;

//움직인 거리에서 상어의 위치가 위쪽의 왼쪽부터 아래의 오른쪽까지 정렬하는 struct
bool cmp(const pos& p, const pos& q) {
	if (p.h == q.h) return p.y < q.y;
	return p.h < q.h;
}

pos1 shark[1]; // 상어의 정보
vector<pos> Vec; // 움직인 당 먹은 물고기의 정보
queue<pos> Q; // 상어의 움직임 정보

void BFS(int hang, int yal);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] >= 1 && board[hang][yal] <= 6) fish++; // 물고기의 갯수 체크..
			if (board[hang][yal] == 9) shark[0] = { hang, yal, 2, 0 }; // 상어의 정보 입력
		}
	}
	//물고기가 한마리도 없으면 출력
	if (fish == 0) {
		printf("%d\n", result);
		return 0;
	}
	BFS(shark[0].H, shark[0].Y);
	printf("%d\n", result);

	return 0;
}

void BFS(int hang, int yal) {
	// 현재의 상어의 위치 체크
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	int movecnt = 0; // 움직인 횟수
	while (!Q.empty()) {
		int sz = Q.size();
		// queue에 들어있는만큼만 움직이면서
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// 상어의 크기와 같거나 작을 때 및 확인한 칸이 아니라면
				if (board[newY][newX] <= shark[0].size && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
					// 만약 물고기의 크기가 상어의 크기보다 작거나 물고기가 없는 곳이 아니라면 물고기 위치 저장
					if (board[newY][newX] > 0 && board[newY][newX] < shark[0].size) {
						Vec.push_back(pos({ newY, newX }));
					}
				}
			}
		}
		movecnt++; // 상어 이동횟수 증가
		// 물고기가 상어에 잡힌 곳이 있다면
		if (Vec.size() != 0) {
			shark[0].cnt++; // 상어가 물고기를 먹은 횟수 증가
			if (shark[0].cnt == shark[0].size) { // 만약 상어의 크기와 물고기 먹은 횟수가 갔다면 먹은 횟수 초기화 상어의 크기 증가
				shark[0].cnt = 0;
				shark[0].size++;
			}
			// 물고기를 먹은 것 중 위쪽의 왼쪽부터 아래쪽의 오른쪽까지 정렬..
			sort(Vec.begin(), Vec.end(), cmp);
			// 상어의위치 이동
			board[hang][yal] = 0;
			board[Vec[0].h][Vec[0].y] = 9;
			// 결과값에 움직임 저장..
			result += movecnt;
			movecnt = 0;
			// 초기화
			while (!Q.empty()) Q.pop();
			memset(check, false, sizeof(check));
			// 상어의 위치를 다시 넣기
			Q.push(pos({ Vec[0].h, Vec[0].y }));
			check[Vec[0].h][Vec[0].y] = true;
			hang = Vec[0].h, yal = Vec[0].y; // 상어의 위치 초기화..
			Vec.clear(); // 먹었던 물고기 초기화..
		}
	}
}