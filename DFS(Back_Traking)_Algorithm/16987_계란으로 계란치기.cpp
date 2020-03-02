/*
	계란으로 계란치기는 왼쪽부터 오른쪽으로 계란을 이동하면서 계란이 가지고있는
	내구도와 무게를 따져가며 깨지는지 안깨지는 판단하는 문제이다.

	브루트포스(재귀)를 이용하여 풀어보았다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


int N;
bool check[8];
int result;

typedef struct _pos {// 계란 각각의 내구도와 무게를 받기위해..
	int S, W;
}pos;

vector<pos> Vec; // 각각의 계란의 무게와 내구도를 넣음..

void solve(int depth);

int main() {
	scanf("%d", &N);
	for (int s, w, i = 0; i < N; i++) {
		scanf("%d %d", &s, &w);
		Vec.push_back(pos({ s, w }));
	}

	solve(0);
	printf("%d\n", result);


	return 0;
}

void solve(int depth) { // depth는 왼쪽계란부터 오른쪽으로 계란을 생각..

	if (depth == N) { // 맨 오른쪽 계란이 끝나고 나면 몇개가깨졌는지 판단.
		int cnt = 0;
		for (int i = 0; i < depth; i++) {
			if (check[i]) cnt++;
		}
		if (result < cnt) result = cnt;
		return;
	}

	if (check[depth]) solve(depth + 1); // 계란을 손에 쥐었을 때 깨진계란이면 넘어간다.


	else {
		bool flag = false;

		for (int s = 0; s < Vec.size(); s++) {// 손에 쥐고있는계란으로 깰 수 있는 모든 계란 판단..

			if (depth == s) continue; // 손에 쥐고있는 계란과 같은 계란이면 넘어간다..

			if (!check[s]) {
				flag = true;
				int prevFirst = Vec[depth].S;
				int prevSecond = Vec[s].S;

				Vec[depth].S -= Vec[s].W; // 손에 쥐고있는계란 내구도..
				Vec[s].S -= Vec[depth].W; // 손에 쥐고있는 계란으로 하나의 계란을 깬 내구도..

				if (Vec[depth].S <= 0) check[depth] = true; // 계란이 깨졋으면 check == true
				if (Vec[s].S <= 0) check[s] = true;

				solve(depth + 1); 
				check[depth] = false; // recover..
				check[s] = false;
				Vec[depth].S = prevFirst;
				Vec[s].S = prevSecond;
			}
		}

		if (!flag) solve(depth + 1); // 아무것도 깰 것이 없을 때 그냥 내려놓는 방법..
	}
}