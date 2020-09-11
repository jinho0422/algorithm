#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N;
int board[1002];
int dij_board[1002];

typedef struct _pos {
	int j, m, c; // j : ������ġ, m : ������ �� �ִ� Ƚ��, c : ���ݱ��� ������ Ƚ��
}pos;

struct cmp { // �ּҷ� ������ Ƚ������ ���ʴ�� ������ ���� ����
	bool operator() (pos p, pos q) {
		return p.c > q.c;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

void BFS(int start, int move, int cnt);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	// ������Ʈ�� �������� dij_board�� Max������ �ʱ�ȭ
	for (int i = 1; i < N; i++) {
		dij_board[i] = INF;
	}
	BFS(0, 0, 0);
	return 0;
}

void BFS(int start, int move, int cnt) {
	Q.push(pos({start, board[start], cnt}));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		// �������� ���������� ���
		if (p.j == N - 1) {
			printf("%d\n", p.c);
			return;
		}
		//������ ��ġ���� 1~ p.m���� �̵��� �� �ִ� ��������
		for (int i = 1; i <= p.m; i++) {
			if (p.j + i > N - 1) continue; // �������� �� �� �� ���� ���̸� continue..
			if (dij_board[p.j + i] > dij_board[p.j] + 1) { // ���� �����ؾߵǴ� ���� ������ ������ Ƚ���� + 1���� ũ�� 
				dij_board[p.j + i] = dij_board[p.j] + 1; // �����δ�..
				Q.push(pos({ p.j + i, board[p.j + i], p.c + 1 }));
			}
		}
	}
	//������ ���� ������ -1 ���
	printf("-1\n");
}