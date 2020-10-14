#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, D;
int board[15][15];
int tmpBoard[15][15]; // 성에 궁수를 넣고 board의 몬스터를 카피하기 위해..
int atacker[3]; // 성의 몇열에 궁수가 들어가는지..
int die[3]; // 한턴당 죽은 몬스터의 넘버를 넣는 배열
bool check[15];
int result; // 결과값
int tmpNum; // 몬스터의 수를 카피하기위해..

typedef struct _pos {
	int h, y; // h : hang, y : yal, flag : 몬스터가 죽었는지 살았는지
	bool flag;
}pos;
pos monster[225]; // 몬스터의 hang, yal을 넣는다.
int num = 0; // 몬스터의 수

bool cmp (const pos& p, const pos& q) { // hang이 큰거부터하면서 hang이 같을 경우 yal이 작은거부터
	if (p.y == q.y) return p.h > q.h;
	return p.y < q.y;
}

vector<pos> Vec;

void DFS(int depth, int start);

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &D);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) monster[num++] = { hang, yal, false }; // 몬스터 저장
		}
	}
	DFS(0, 0);
	//출력
	printf("%d\n", result);
	return 0;
}

int solve() {
	int cnt = 0; // 죽은 몬스터 수

	while (1) {
		for (int i = 0; i < 3; i++) die[i] = -1; // 죽은 몬스터의 번호를 넣기..
		// 궁수당 몬스터를 모두 보면서 가장 가까우면서 왼쪽에 위치한 아이를 찾는다.
		for (int i = 0; i < 3; i++) {
			int sh = N, sy = atacker[i]; // 궁수의 위치
			int minDir = 987654321; // 궁수가 죽인 최소거리의 몬스터를 찾기위해
			for (int j = 0; j < Vec.size(); j++) {
				if (Vec[j].flag) continue; // 죽거나 없어진 몬스터는 continue..
				int dir = abs(sh - Vec[j].h) + abs(sy - Vec[j].y); // 궁수와 몬스터의 거리
				if (dir <= D) { // 화살이 닫는곳일때
					if (minDir > dir) { // 가장 가까우면
						minDir = dir;
						die[i] = j; // 죽은 몬스터의번호를 저장..
					}
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if (die[i] == -1) continue; // 궁수가 아무도 못죽였을 경우
			if (!Vec[die[i]].flag) { // 죽지 않은 몬스터이면
				Vec[die[i]].flag = true;
				cnt++; // 죽인다..
				tmpNum--;// 몬스터갯수--;
				if (tmpNum == 0) return cnt; // 몬스터가 모두 없어졌을 때 return cnt;;
			}
		}
		// 몬스터를 모두 아래로 한칸 내려준다..
		for (int i = 0; i < Vec.size(); i++) {
			if (Vec[i].flag) continue; // 죽은 몬스터는 가만히 놔두고
			Vec[i].h++; // 아래로 한칸 내려서 만약 궁까지 도착하면 없어지게 만든다..
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
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // 몬스터 카피..
		//초기화
		Vec.clear();
		tmpNum = num;
		// 몬스터를 vector에 담고 sort..
		for (int i = 0; i < num; i++) Vec.push_back(pos({ monster[i].h, monster[i].y, false }));	
		sort(Vec.begin(), Vec.end(), cmp);
		int sum = solve();
		// 결과값 갱신
		if (result < sum) result = sum;
		return;
	}
	// 궁수를 놓을 열의 위치를 atacker배열에 넣는다..
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