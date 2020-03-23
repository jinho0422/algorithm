/*
	N(2<= N <= 10000)���� ������ �̷���� ���� �ִ�. �̵� �� ��� �� ���̿��� �ٸ��� ��ġ�Ǿ� �־ ������ �ٴ� �� �ִ�.
	�� ���� ���� ������ ���� �ΰ� ��ǰ�� �����ϴ� ���� �ϰ� �ִ�. ��ǰ�� �����ϴ� ���� ���忡�� �ٸ� ��������
	���� ���̴� ��ǰ�� �����ؾ��� ���� ����� �Ѵ�. �׷��� ������ �ٸ����� �߷������� �ֱ� ������ ���δ�� ��ǰ�� �ű� �� ����.
	���� �߷������� �ʰ��ϴ� ���� ��ǰ�� �ٸ��� ������ �Ǹ� �ٸ��� �������� �ȴ�.
	�� �� �̵����� �ű� �� �ִ� ��ǰ���� �߷��� �ִ��� ���ϴ� �˰��� ����..

	���� ���� �� ���� ���̿� ���� ���� �ٸ��� ���� ���� �����Ƿ� �Ѱ��� ������ �湮 �� �� �ִٴ�
	�������� dijkstra�˰����� ����Ͽ���. �׸��� dijkstra�� �׻� INF(214700000)���� �߾�����
	�� ���������� dijkstra�� 0���� ���(�ٸ��� �߷��� 1���� ũ�ų� ���� ������)�Ͽ� �ִ밪�� �����ϴ� �˰�����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int dij_board[10001];
int factoryStart, factoryEnd; // ������ �ִ� �ΰ�..

typedef struct _pos {
	int B, W;
}pos;
vector<pos> Vec[10001]; // �� ���ÿ��� �ٸ����÷� ���� ���ÿ� �ٸ����� �ߵ� �� �ִ� ���� W�� ������ struct

void solve(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Vec[a].push_back(pos({ b, c }));// ���ô� �瓇���̹Ƿ�..
		Vec[b].push_back(pos({ a, c }));
	}
	scanf("%d %d", &factoryStart, &factoryEnd);

	solve(factoryStart); // ������ ����..
	printf("%d\n", dij_board[factoryEnd]);

	return 0;
}

void solve(int start) {
	queue<pos> Q;
	dij_board[start] = 2147000000; // ������ ���������� �ִ밪���� �ְ�..BFS_dijkstra
	Q.push(pos({ start, 2147000000 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		if (p.B == factoryEnd || p.W < dij_board[p.B]) continue; // �������� �����̰ų� dijkstra�� �־��ִ� ���� �� ���� �ִ��߷��̹Ƿ� ������ �� �ʿ䰡 �����Ƿ� continue..

		int sz = Vec[p.B].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p.B][s].B; // ���� ��..
			int second = Vec[p.B][s].W; // ���°��� �ٸ��� ��ƿ �� �ִ� �߷�..

			if (second > dij_board[p.B]) second = dij_board[p.B]; // ���� ���� ��ġ���� ��ƿ �� �ִ� �ִ��߷����� ���� ���� ��ƿ �� �ִ� �ٸ� �߷��� ũ�� ���翡�� ��ƿ �� �ִ� �߷�����..

			if (dij_board[first] < second) { // ���� ���°��� ��ƿ �� �ִ� �߷��� �ִ밪���� ���� �� ��������..
				dij_board[first] = second;
				Q.push(pos({ first, dij_board[first] }));
			}
		}
	}
}