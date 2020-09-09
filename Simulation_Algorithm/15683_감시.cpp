#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int board[9][9];
int tmpBoard[9][9];
int tmp[9];
int dirY[4] = { 0, 1, 0, -1 }; // 0 : -> , 1 : 아래, 2 : <-, 3: 위쪽
int dirX[4] = { 1, 0, -1, 0 };
bool check[8];
int zero;
int zeroCnt;
int minResult;

typedef struct _pos {
	int h, y, cc;
}pos;
vector<pos> Vec;

void DFS(int depth, int endd);

int main() {
	//입력
	minResult = 987654321;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 0) zero++; //CCTV가 돌아가지 않을 때 0인 곳
			if (board[hang][yal] != 0 && board[hang][yal] != 6) Vec.push_back(pos({ hang, yal, board[hang][yal] })); // cctv
		}
	}
	int sz = Vec.size();
	DFS(0, sz);
	printf("%d\n", minResult);
	return 0;
}


void view(int start, int dir) {
	int cctv = Vec[start].cc;
	vector<int> dirVec; // 각 cctv에서 볼 수 있는 방향을 dirVec에 넣는다.
	dirVec.push_back(dir);
	switch(cctv) {
	case 1 :
		break;
	case 2 :
		dir += 2;
		if (dir > 3) dir -= 4;
		dirVec.push_back(dir);
		break;
	case 3 :
		dir += 1;
		if (dir > 3) dir -= 4;
		dirVec.push_back(dir);
		break;
	case 4 :
		for (int i = 1; i < 3; i++) {
			dir -= 1;
			if (dir < 0) dirVec.push_back(dir + 4);
			else dirVec.push_back(dir);
		}
		break;
	case 5 :
		for (int d = 0; d < 4; d++) {
			if (d == dir) continue;
			dirVec.push_back(d);
		}
		break;
	}
	// 방향으로 사각지대를 없앤다..
	for (int d = 0; d < dirVec.size(); d++) {
		int hang = Vec[start].h, yal = Vec[start].y;
		while (1) {
			int newY = hang + dirY[dirVec[d]];
			int newX = yal + dirX[dirVec[d]];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || tmpBoard[newY][newX] == 6) break;

			if (tmpBoard[newY][newX] == -1 || (tmpBoard[newY][newX] >= 1 && tmpBoard[newY][newX] <= 5)) {
				hang = newY, yal = newX;
				continue;
			}

			if (tmpBoard[newY][newX] == 0) {
				tmpBoard[newY][newX] = -1;
				zeroCnt--;
				hang = newY, yal = newX;
			}
		}
	}
}

void DFS(int depth, int endd) {
	if (depth == endd) {
		memcpy(tmpBoard, board, sizeof(tmpBoard));
		zeroCnt = zero;
		for (int i = 0; i < depth; i++) {
			view(i, tmp[i]);
		}
		if (minResult > zeroCnt) minResult = zeroCnt; // 결과값 갱신..
		return;
	}
	//각 cctv의 회전방향을 가져온다.. i : 0 이면 ->부터시작해서  1: 아래 2: 왼쪽 3: 위
	for (int i = 0; i < 4; i++) {
		if (!check[depth]) {
			check[depth] = true;
			tmp[depth] = i;
			DFS(depth + 1, endd);
			tmp[depth] = 0;
			check[depth] = false;
		}
	}
}