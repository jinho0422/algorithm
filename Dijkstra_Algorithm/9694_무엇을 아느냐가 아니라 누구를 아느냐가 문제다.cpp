#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
int dij_board[22];
int link[22]; // ����ȭ�� ��������� ������踦 ������������.
bool flag;

typedef struct _pos {
	int B, W;
}pos;

bool cmp1(const pos& p, const pos& q) { // ������� ���谡 1, 2, 3, 4������ �� �� �ְ��Ϸ���
	return p.W < q.W;
}

vector<pos> Vec[21]; // �ѻ���� ����� ����� ��ȣ�� �� ������ ������ �ִ´�.
queue<int> Q;
stack<int> S; // ������� ��Ʈ�� �̾Ƴ��� ����..

void BFS(int start);

int main() {
	//�Է�
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		memset(link, 0, sizeof(link)); // ������� �ʱ�ȭ..
		for (int i = 1; i < M; i++) {
			dij_board[i] = INF;
		}
		for (int a, b, c, i = 0; i < N; i++) {
			scanf("%d %d %d", &a, &b, &c);
			Vec[a].push_back(pos({ b, c }));
			Vec[b].push_back(pos({ a, c }));
		}
		// ���谡 �����ٺ��� ���ĵ� �� �ֵ���
		for (int i = 0; i < M; i++) {
			sort(Vec[i].begin(), Vec[i].end(), cmp1);
		}
		flag = false; // ������ �ϴ� ������� �����ߴ��� ����.
		BFS(0);
		//���
		printf("Case #%d: ", t);
		if (flag) {
			S.push(M - 1);
			while (1) {
				int s = S.top();
				if (s == 0) break;
				S.push(link[s]);
			}
			while (!S.empty()) {
				printf("%d ", S.top());
				S.pop();
			}
		}
		else printf("-1");
		printf("\n");
		for (int i = 0; i < M; i++) Vec[i].clear(); // �ʱ�ȭ
	}
	return 0;
}

void BFS(int start) {
	Q.push(start);

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		if (p == M - 1) {
			flag = true; // �������ϴ� ����� ������ flag : true
		}
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s].B;
			int second = Vec[p][s].W;
			//������Ʈ�� ����ؼ�
			if (dij_board[first] > dij_board[p] + second) {
				dij_board[first] = dij_board[p] + second;
				Q.push(first);
				link[first] = p; // ���� �ּ��� ģ�е��� �� �� ������ link�� �����Ų��.
			}
		}
	}
}