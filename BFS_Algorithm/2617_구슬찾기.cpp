/*
	모양은 같으나, 무게가 모두 다른 N개의 구슬이 있다. N은 홀수이며, 구슬에는 번호가 1,2,.... N으로 붙어있다.
	이 구슬 중에서 무게가 전체의 중간인(무개 순서로(N + 1) 2번째) 구슬을 찾기 위해서 아래와 같은 일을 하려고한다.
	우리에게 주어진 것은 양팔 저울이다. 한 쌍의 구슬을 골라서 양팔 저울의 양쪽에 하나씩 올려보면
	어느쪽이 무거운가를 알 수 있다. 이렇게 M개의 쌍을 골라서 각각 양팔 저울에 올려서 어느 것이 무거운가를 모두 알아냈다.
	이 결과를 이용하여 무게가 중간이 될 가능성이 전혀 없는 구슬들을 먼저 제외한다.

	M 개의 쌍에 대한 결과를 보고 무게가 중간인 구슬이 될 수 없는 구슬의 개수를 구하는 알고리즘을 구현해라..

	이를 구현하기 위해 BFS를 활용하여 자신보다 크기가 작은 갯수, 또는 자신보다 크기가 큰 갯수를 확인하는
	알고리즘을 구현하여 판단..
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N, M;
int cnt;
bool check[101];
bool num_check[101];

vector<int> big_Vec[100]; // 자신보다 큰 구슬을 넣는 vector
vector<int> small_Vec[100]; // 자신보다 작은 구슬을 넣는 vector

void big_BFS(int start);
void small_BFS(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		small_Vec[a].push_back(b);
		big_Vec[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		if (!num_check[i]) { // 자신이 중간 구슬인지 아직 모르면..
			memset(check, false, sizeof(check)); // check배열 초기화..
			big_BFS(i);// 자신보다 큰 구슬이 몇개인지 판단하기 위한 BFS..
		}
		if (!num_check[i]) {
			memset(check, false, sizeof(check)); // check배열 초기화..
			small_BFS(i); // 자신보다 작은 구슬이 몇개인지 판단하기 위한 BFS..
		}
	}
	printf("%d\n", cnt);

	return 0;
}

void big_BFS(int start) {
	queue<int> Q;
	check[start] = true;
	Q.push(start);
	int num = 0;

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = big_Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = big_Vec[p][s];
			if (!check[first]) {
				check[first] = true;
				num++;
				if (num > N / 2) { // 자신보다 큰 구슬이 전체의 구슬의 반보다 많으면 중간 구슬이 될 수 없으므로
					cnt++; // 결과값 + 1
					num_check[start] = true;
					return;
				}
				Q.push(first);
			}
		}
	}
}

void small_BFS(int start) {
	queue<int> Q;
	check[start] = true;
	Q.push(start);
	int num = 0;

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = small_Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = small_Vec[p][s];
			if (!check[first]) {
				check[first] = true;
				num++;
				if (num > N / 2) { // 자신보다 작은 구슬이 전체 구슬의 반보다 많으면 중간 구슬이 될 수 없으므로..
					cnt++; // 결과값 + 1
					num_check[start] = true;
					return;
				}
				Q.push(first);
			}
		}
	}
}