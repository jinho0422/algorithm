#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int N, M, K;
int board[51][51];
int tmpBoard[51][51];
bool check[6];
int tmp[6];
int result;


typedef struct _pos {
	int R, C, S;
}pos;

vector<pos> Vec;

void DFS(int depth);

int main() {
	//입력
	result = 2147000000;
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int r, c, s, i = 0; i < K; i++) {
		scanf("%d %d %d", &r, &c, &s);
		Vec.push_back(pos({ r -1, c -1, s })); // board 배열이 0, 0부터 시작하므로 행,열을 -1씩 빼준다,
	}
	DFS(0);
	printf("%d\n", result);
	return 0;
}

void spinBoard(int start) {
	pos p = Vec[start]; // 회전하는 요소가 들어있는 vector..
	int sh = p.R - p.S, sy = p.C - p.S, fh = p.R + p.S, fy = p.C + p.S;
	while (1) {
		if (sh == fh && sy == fy) break; // 시작점과 끝점이 같으면 종료..
		int firstBoard = tmpBoard[sh][sy]; // 처음 스타트점을 기억하고
		// 회전..
		for (int hang = sh; hang < fh; hang++) {
			tmpBoard[hang][sy] = tmpBoard[hang + 1][sy];
		}
		for (int yal = sy; yal < fy; yal++) {
			tmpBoard[fh][yal] = tmpBoard[fh][yal + 1];
		}
		for (int hang = fh; hang > sh; hang--) {
			tmpBoard[hang][fy] = tmpBoard[hang - 1][fy];
		}
		for (int yal = fy; yal > sy + 1; yal--) {
			tmpBoard[sh][yal] = tmpBoard[sh][yal - 1];
		}
		tmpBoard[sh][sy + 1] = firstBoard; // 마지막에 넣는다
		sh++, sy++, fh--, fy--;	
	}
}

void DFS(int depth) {
	if (depth == K) {
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // 순열마다 tmpBoard를 통해 회전을 시키기 위해  board 배열 복사
		for (int i = 0; i < depth; i++) {
			spinBoard(tmp[i]); // 보드 회전 함수..
		}
		//결과값 갱신..
		for (int hang = 0; hang < N; hang++) {
			int sum = 0;
			for (int yal = 0; yal < M; yal++) {
				sum += tmpBoard[hang][yal];
			}
			if (result > sum) result = sum;
		}
		return;
	}
	//Vector에 들어있는 회전에 필요한 요소를 순열로 뽑아 tmp에 저장.
	for (int i = 0; i < K; i++) {
		if (!check[i]) {
			check[i] = true;
			tmp[depth] = i;
			DFS(depth + 1);
			tmp[depth] = 0;
			check[i] = false;
		}
	}
}