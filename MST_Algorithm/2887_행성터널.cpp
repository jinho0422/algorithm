/*
	https://www.acmicpc.net/problem/2887
	N개의 행성으로 이루져있고 이 행성을 효율적으로 지배하기 위해서 행성을 연결하는 터널을 만들려고한다.
	행성은 3차원 좌표위의 한 점으로 생각하면 된다. 두 행성 x, y, z를 터널로 연결할 때 드는 비용은 각각의 x y z를 뺐을 때의 절대값의 최소이다.
	터널을 총 N -1개건설해서 모든 행성이 서로 연결되게 하려고한다. 최소비용을 구하는 알고리즘 구현

	N개의 행성에서 총 N -1터널을 건설해서 모든 행성이 서로 연결되게 하려고 하므로 유니온파인트를 사용하여
	모든 행성이 연결될 수 있도록 MST를 활용하여 알고리즘 구현..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N;
int parent[100001];// 유니온 파인트를 사용하기 위해..
int result;
int cnt;

typedef struct _pos1 { // 각각의 x, y, z와  그 행성번호를 넣기위한 struct 
	int n, b;
}pos1;

bool cmp (const pos1 &p, const pos1 &q) { // x, y, z각각에서 행성끼리의 최소 비용을 설정하기 위한 정렬 struct
	return p.b > q.b;
}
pos1 X[100001];// 각 행성의 번호와 x좌표
pos1 Y[100001];// 각 행성의 번호와 y좌표
pos1 Z[100001];// 각 행성의 번호와 z좌표

typedef struct _pos { // 행성들의 행성 번호와 최소 비용을 넣을 수 있는 struct 
	int x, y, W;
}pos;

bool cmp1(const pos &p, const pos &q) { // 백터안에 있는 최소비용을 오름차순으로 정렬하기 위한 struct
	return p.W < q.W;
}
vector<pos> Vec;

int find_(int x) { // 자기 자신의 최상위를 찾아주는 find 함수
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) { // 유니온 파인드를 해주기 위해 최초로 자기 자신이 최상위로..(배열이 가지고 있는 값은 자기 최상위 위치)
		parent[i] = i;
	}

	for (int a, b, c, i = 1; i <= N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		X[i] = { i, a };
		Y[i] = { i, b };
		Z[i] = { i, c };
	}
	sort(X + 1, X + N + 1, cmp);
	sort(Y + 1, Y + N + 1, cmp);
	sort(Z + 1, Z + N + 1, cmp);

	for (int i = 1; i < N; i++) { // 각각의 행성들 x, y, z의 다리 건설 최소값을 넣어준다.
		Vec.push_back(pos({ X[i].n, X[i + 1].n, abs(X[i].b - X[i + 1].b) }));
		Vec.push_back(pos({ Y[i].n, Y[i + 1].n, abs(Y[i].b - Y[i + 1].b) }));
		Vec.push_back(pos({ Z[i].n, Z[i + 1].n, abs(Z[i].b - Z[i + 1].b) }));
	}

	sort(Vec.begin(), Vec.end(), cmp1); // MST를 사용하기 위한 정렬..

	for (int s = 0; s < Vec.size(); s++) { // 백터의 size만큼 돌면서 유니온해준다..
		int a_head = find_(Vec[s].x);
		int b_head = find_(Vec[s].y);

		if (a_head != b_head) {// find를 해주었을 때 최상위 값이 다르면 
			parent[a_head] = b_head; // 합쳐준다..
			result += Vec[s].W;// 다리건설 비용을 더해준다..
			cnt++;// 건설된 다리를 세어준다..
			if (cnt == N - 1) break;// 모든 행성이 연결되는 다리가 만들어지면 break.
		}
	}
	printf("%d\n", result);
	return 0;
}