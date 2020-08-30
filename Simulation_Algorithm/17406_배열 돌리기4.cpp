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
	//�Է�
	result = 2147000000;
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int r, c, s, i = 0; i < K; i++) {
		scanf("%d %d %d", &r, &c, &s);
		Vec.push_back(pos({ r -1, c -1, s })); // board �迭�� 0, 0���� �����ϹǷ� ��,���� -1�� ���ش�,
	}
	DFS(0);
	printf("%d\n", result);
	return 0;
}

void spinBoard(int start) {
	pos p = Vec[start]; // ȸ���ϴ� ��Ұ� ����ִ� vector..
	int sh = p.R - p.S, sy = p.C - p.S, fh = p.R + p.S, fy = p.C + p.S;
	while (1) {
		if (sh == fh && sy == fy) break; // �������� ������ ������ ����..
		int firstBoard = tmpBoard[sh][sy]; // ó�� ��ŸƮ���� ����ϰ�
		// ȸ��..
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
		tmpBoard[sh][sy + 1] = firstBoard; // �������� �ִ´�
		sh++, sy++, fh--, fy--;	
	}
}

void DFS(int depth) {
	if (depth == K) {
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // �������� tmpBoard�� ���� ȸ���� ��Ű�� ����  board �迭 ����
		for (int i = 0; i < depth; i++) {
			spinBoard(tmp[i]); // ���� ȸ�� �Լ�..
		}
		//����� ����..
		for (int hang = 0; hang < N; hang++) {
			int sum = 0;
			for (int yal = 0; yal < M; yal++) {
				sum += tmpBoard[hang][yal];
			}
			if (result > sum) result = sum;
		}
		return;
	}
	//Vector�� ����ִ� ȸ���� �ʿ��� ��Ҹ� ������ �̾� tmp�� ����.
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