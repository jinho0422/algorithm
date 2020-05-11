/*
	https://www.acmicpc.net/problem/10282
	a�� �ٸ� ��ǻ�� b�� �����Ѵٸ�, b�� �����Ǹ� �׷κ��� ���� �ð� �� a�� �����ȴ�.
	������ �����Ǳ� ���� �ɸ��� �ð��̹Ƿ� �ּ��� �ð��� ã�ƾ��Ѵ�.
	���ͽ�Ʈ�� �˰����� ���� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int n, d, c;
int dij[10001];

typedef struct _pos { 
	int A, S;
}pos;

typedef struct _pos1 {
	int B, co;
}pos1;

vector<pos> Vec[10001];
queue<pos1> Q;

void solve(int start);

int main() {
	int T; scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &n, &d, &c);
		for (int i = 1; i <= n; i++) { // ������ �ڽŻ��� dij�迭�� INF�� ���ش�.
			if (i == c) {
				dij[i] = 0;
				continue;
			}
			dij[i] = INF;
		}
		for (int a, b, s, i = 0; i < d; i++) { // ������ ���踦 Vector�� ���� ��������ش�.(Vec[������ų �� �ִ� ��ǻ��] = {�����ɼ� �ִ� ��ǻ��, �ð�}
			scanf("%d %d %d", &a, &b, &s);
			Vec[b].push_back(pos({ a, s }));
		}
		solve(c);
		int cnt = 0; // ���� ��ǻ�� ���� 
		int max_time = 0; // �ּ��� �ð��� ���ϱ� ���� ������ ��ǻ���� �ִ��� ���� ã���ش�. 
		for (int i = 1; i <= n; i++) {
			if (dij[i] == INF) continue; //�������� ���� ��ǻ�ʹ� continue..
			cnt++;
			if (max_time < dij[i]) max_time = dij[i];
		}
		printf("%d %d\n", cnt, max_time);
		for (int i = 1; i <= n; i++) { // vector clear..
			Vec[i].clear();
		}
		
	}
	return 0;
}

void solve(int start) {
	Q.push(pos1({ start, 0 }));
	while (!Q.empty()) {
		pos1 p = Q.front();
		Q.pop();

		int sz = Vec[p.B].size(); // ������ų �� �ִ� ��ǻ�Ϳ��� ������ �� �ִ� ��ǻ�� ����..
		for (int s = 0; s < sz; s++) { 
			int first = Vec[p.B][s].A;
			int second = Vec[p.B][s].S;

			if (dij[first] > p.co + second) { // ������ �� �ִ� ��ǻ�Ͱ� ������ų �� �ִ� ��ǻ�� �ð� + ������ ��ǻ�Ͱ� ������ �ð����� ũ�� ����..  
				dij[first] = p.co + second;
				Q.push(pos1({first, dij[first]}));
			}
		}
	}
}