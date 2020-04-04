/*
	https://www.acmicpc.net/problem/12851
	�����̰� ������ ã�� �� �ִ� ���� ���� �ð��� �� �ð��� ã�� �� �ִ�
	����� ���� ã�ƾ� �ϹǷ� dijkstra + BFS�� Ȱ���� �˰��� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000 // dij �ʱ�ȭ�� ���� INF
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N, K;
int dij_board[100001];
int min_result; // �������� �����ϱ� ���� �ּҽð����� int
int cnt; // �ּҽð��� �� �� �����ϴ��� count int

void solve(int start);

typedef struct _pos { //c == �����̰� �����ϴ� ��, t == c�� �����ϴµ� �ɸ� �ð�..
	int c, t;
}pos;

struct cmp { // �ּ��� �ð����� priority_queue���� �̾Ƴ��� ����..
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

int main() {
	min_result = INF;
	scanf("%d %d", &N, &K);
	for (int i = 0; i <= 100000; i++) { // dij_board �ʱ�ȭ..
		dij_board[i] = INF;
	}
	
	solve(N); // �������� ���� ��ġ�������� BFS
	printf("%d\n%d\n", min_result, cnt);
	return 0;
}

void solve(int start) {
	priority_queue<pos, vector<pos>, cmp> Q;
	dij_board[start] = 0;
	Q.push(pos({ start, 0 })); // �������� ���� ��ġ�� ���� �ð� 0
	

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (min_result < p.t) continue; // ���ŵ� �ּҽð����� ũ�� continue..

		if (p.c == K) { // �����̰� ������ ã���� ��..
			if (min_result > dij_board[p.c]) { // �ּҽð��� ������ �������� 
				min_result = dij_board[p.c]; // �����ϰ�
				cnt = 1; // conunt = 1
			}
			else if (min_result == dij_board[p.c]) {
				cnt++; // ������ count++
			}
		}

		if (p.c + 1 <= 100000) { // �����̰� ��ĭ ������ �� �� 100000���� ������
			if (dij_board[p.c + 1] >= dij_board[p.c] + 1) { // ������ ���� ������ �ð� + 1���� ũ��
				dij_board[p.c + 1] = dij_board[p.c] + 1; // ����
				Q.push(pos({ p.c + 1, p.t + 1 }));
			}
		}

		if (p.c - 1 >= 0) { // �����̰� ��ĭ �ڷ� �� ��  0 ���� ������
			if (dij_board[p.c - 1] >= dij_board[p.c] + 1) { // ������ ���� ������ �ð� + 1���� ũ��
				dij_board[p.c - 1] = dij_board[p.c] + 1;// ����
				Q.push(pos({ p.c - 1, p.t + 1 }));
			}
		}

		if (p.c * 2 <= 100000) { // �����̰� �����̵�(������ġ * 2) �� �� 100000���� ������
			if (dij_board[p.c * 2] >= dij_board[p.c] + 1) { // ������ ���� ������ �ð� + 1���� ũ��
				dij_board[p.c * 2] = dij_board[p.c] + 1;// ����
				Q.push(pos({ p.c * 2, p.t + 1 }));
			}
		}
	}
}