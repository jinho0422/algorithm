/*
	�����̴� ������ ���ٲ����� �ϰ� �ִ�. �����̴� ���� �� N(0 �� N �� 100,000)�� �ְ�,
	������ �� K(0 �� K �� 100,000)�� �ִ�. �����̴� �Ȱų� �����̵��� �� �� �ִ�. 
	����, �������� ��ġ�� X�� �� �ȴ´ٸ� 1�� �Ŀ� X-1 �Ǵ� X+1�� �̵��ϰ� �ȴ�. 
	�����̵��� �ϴ� ��쿡�� 0�� �Ŀ� 2*X�� ��ġ�� �̵��ϰ� �ȴ�.
	�����̿� ������ ��ġ�� �־����� ��, �����̰� ������ ã�� �� �ִ� 
	���� ���� �ð��� �� �� ������ ���ϴ� �˰��� ����.

	�����̵��� �ϴ� ��쿡�� ����ϴ� �ð��� 0���̹Ƿ� �ּ��� �ð��� ���ŵ� �� �ִ�.
	��, �������� �� �湮�� �� �ִٴ� ���̴�. ���� ���ͽ�Ʈ�� �˰������� ����.

*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
int dij_board[100001]; // dijkstra_algorithm�� ����..
int dirX[3] = { -1, 1, 2 };

typedef struct _pos { // ����� ��ġ �� �� �������� �ð� struct
	int s, t;
}pos;

struct cmp { // priority_queue�� ���� �ð��� ���� �ͺ��� ������ �ϱ� ���� cmp
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;

int main() {
	scanf("%d %d", &N, &K);
	
	for (int i = 0; i <= 100000; i++) dij_board[i] = INF;

	dij_board[N] = 0;
	Q.push(pos({ N, 0 })); // pq�� ����� �������� �ð� 0�ʸ� �ִ´�.
	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (dij_board[K] <= p.t) continue; // ��ϰ� �Ҹ��� �ð��� ������ ã�� �ٸ� �̵����⺸�� ũ�� continue..

		//printf("%d %d\n", p.s, p.t);

		for (int dir = 0; dir < 3; dir++) {
			if (dir != 2) {
				int newN = p.s + dirX[dir];

				if (newN < 0 || newN > 100000) continue; // ������ ����� continue..

				if (dij_board[newN] > p.t + 1) { // �ɾ �̵�..
					dij_board[newN] = p.t + 1; // �ɾ �̵��ϴ��ϴ� ���� ���� �湮�߾��� �̵��ð����� ������ 
					Q.push(pos({ newN, p.t + 1 })); // ����..
				}
			}
			else { // �����̵�..
				int newN = p.s * dirX[dir]; 
				if (newN < 0 || newN > 100000) continue;

				if (dij_board[newN] > p.t) { // �����̵����ؼ� ���� �湮�ߴ� ����ð����� ������ ����..
					dij_board[newN] = p.t;
					Q.push(pos({ newN, p.t }));
				}
			}
		}
	}
	printf("%d\n", dij_board[K]);

	return 0;
}