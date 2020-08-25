#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
using namespace std;

int N;
int population[11]; // 인구수 저장 배열
bool check[11]; // true : A구역으로 선택된 팀, false B구역으로 선택된 팀
bool linkCheck1[11]; // A구역으로 선택된 팀이 모두 연결되어있는지 판단
bool linkCheck2[11]; // B구역으로 선택된 팀이 모두 연결되어있는지 판단
int minPop; // 결과값
int firstA; // A팀의 첫번째 구역
int secondB; // B팀의 첫번째 구역

vector<int> Vec[11]; // 각 구역이랑 연결된 장소 저장..

void DFS(int endd, int depth, int start);

int main() {
	//입력
	minPop = 2147000000;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &population[i]);
	}
	for (int s, i = 1; i <= N; i++) {
		scanf("%d", &s);
		for (int a, j = 0; j < s; j++) {
			scanf("%d", &a);
			Vec[i].push_back(a);
		}
	}
	// 조합으로 A, B팀을 나눈다.
	for (int s = 1; s <= N / 2; s++) {
		DFS(s, 0, 1);
	}
	//출력
	if (minPop == 2147000000) printf("-1\n");
	else printf("%d\n", minPop);
	return 0;
}
// A팀이 모두연결되어있는지 판단..
bool BFS1(int start, int e) {
	queue<int> Q;
	linkCheck1[start] = true;
	Q.push(start);
	int cnt = 1;
	while(!Q.empty()) {
		int p = Q.front();
		Q.pop();
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			if (check[Vec[p][s]] && !linkCheck1[Vec[p][s]]) {
				linkCheck1[Vec[p][s]] = true;
				Q.push(Vec[p][s]);
				cnt++;
			}
		}
	}
	if (cnt == e) return true;
	else return false;
}
// B팀이 모두 연결되어있는지 판단..
bool BFS2(int start, int e) {
	queue<int> Q;
	linkCheck2[start] = true;
	Q.push(start);
	int cnt = 1;
	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			if (!check[Vec[p][s]] && !linkCheck2[Vec[p][s]]) {
				linkCheck2[Vec[p][s]] = true;
				Q.push(Vec[p][s]);
				cnt++;
			}
		}
	}
	if (cnt == e) return true;
	else return false;
}

void DFS(int endd, int depth, int start) {
	if (depth == endd) {
		//연결 초기화
		memset(linkCheck1, false, sizeof(linkCheck1));
		memset(linkCheck2, false, sizeof(linkCheck2));
		// 각 팀의 기준 구역을 선정
		for (int i = 1; i <= N; i++) {
			if (check[i]) firstA = i;
			else secondB = i;
		}
		bool flagA = false, flagB = false;
		int sumA = 0, sumB = 0;
		flagA = BFS1(firstA, endd);	
		if (flagA) flagB = BFS2(secondB, N - endd);
		
		// 만약 각각의 팀이 모두 연결되어있으면 결과값 갱신..
		if (flagA && flagB) {
			for (int i = 1; i <= N; i++) {
				if (linkCheck1[i]) sumA += population[i];
				if (linkCheck2[i]) sumB += population[i];
			}
			if (minPop > abs(sumA - sumB)) minPop = abs(sumA - sumB);
		}
		return;
	}
	for (int s = start; s <= N; s++) {
		check[s] = true;
		DFS(endd, depth + 1, s + 1);
		check[s] = false;
	}
}