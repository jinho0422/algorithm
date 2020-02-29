/*
 효울적인 해킹 문제는 N개의 컴퓨터로 이루어져있는 회사에서 
 한번의 햌팅으로 여러 개의 컴퓨터를 해킹 할 수 있는 컴퓨터를 해킹하려고하는 문제.
 컴퓨터는 신뢰하는 관계와 신뢰하지 않는 관계로 이루어져 있는데,
 A가 B를 신뢰하는 경우에는 B를 해킹하면 A도 해킹할 수 있다는 것이다.
 

  5초의 시간이라는 것을 활용하여 BFS를 1~N 까지의 컴퓨터를 해킹했을 때 같이 해킹되어지는 컴퓨터의 갯수를 찾아 결과값을 보일 것이다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
bool check[10001]; // 한번체크한 컴퓨터는 또 체크하지 않기위해.
int result;

vector<int> Vec[10001]; // 신뢰관계의 컴퓨터를 입력하기 위해..
queue<int> Q; // 하나의 컴퓨터 해킹으로 해킹할 수 있는 모든 컴퓨터를 체크하기 위해.
queue<int> Q_result; // 오름차순의 결과값을 얻기위해.

int BFS(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[b].push_back(a); // b의 컴퓨터를 해킹하면 a의 컴퓨터는 저절로 해킹..
	}

	for (int i = 1; i <= N; i++) { // 1 ~ N까지의 컴퓨터를 하나씩 살펴보펴 각각의 컴퓨터를 해킹했을 때 어느 컴퓨터가 해킹되는 지 보기위해 BFS를 사용.
		int K = BFS(i); 
		if (result == K) Q_result.push(i); // K갑과 result값이 같으면 같은 크기의 컴퓨터를 해킹.
		else if (result < K) { // 더 크다면 더 많은 컴퓨터를 해킹하므로 지금까지 있었던 결과값을 모두 pop해주고 result를 바꿔주고 결과값 Q에 넣는다.
			while (!Q_result.empty()) Q_result.pop();
			Q_result.push(i);
			result = K;
		}
		memset(check, false, sizeof(check));
	}

	while (!Q_result.empty()) {
		int p = Q_result.front();
		Q_result.pop();
		printf("%d ", p);
	}
	printf("\n");

	return 0;
}

int BFS(int start) {
	check[start] = true;
	Q.push(start);
	int cnt = 0; // 해킹할 수 있는 갯수를 세어준다.

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];

			if (!check[first]) {
				check[first] = true;
				Q.push(first);
				cnt++;
			}
		}
	}
	return cnt;
}