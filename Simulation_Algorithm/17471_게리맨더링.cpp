#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
using namespace std;

int N;
int population[11]; // �α��� ���� �迭
bool check[11]; // true : A�������� ���õ� ��, false B�������� ���õ� ��
bool linkCheck1[11]; // A�������� ���õ� ���� ��� ����Ǿ��ִ��� �Ǵ�
bool linkCheck2[11]; // B�������� ���õ� ���� ��� ����Ǿ��ִ��� �Ǵ�
int minPop; // �����
int firstA; // A���� ù��° ����
int secondB; // B���� ù��° ����

vector<int> Vec[11]; // �� �����̶� ����� ��� ����..

void DFS(int endd, int depth, int start);

int main() {
	//�Է�
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
	// �������� A, B���� ������.
	for (int s = 1; s <= N / 2; s++) {
		DFS(s, 0, 1);
	}
	//���
	if (minPop == 2147000000) printf("-1\n");
	else printf("%d\n", minPop);
	return 0;
}
// A���� ��ο���Ǿ��ִ��� �Ǵ�..
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
// B���� ��� ����Ǿ��ִ��� �Ǵ�..
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
		//���� �ʱ�ȭ
		memset(linkCheck1, false, sizeof(linkCheck1));
		memset(linkCheck2, false, sizeof(linkCheck2));
		// �� ���� ���� ������ ����
		for (int i = 1; i <= N; i++) {
			if (check[i]) firstA = i;
			else secondB = i;
		}
		bool flagA = false, flagB = false;
		int sumA = 0, sumB = 0;
		flagA = BFS1(firstA, endd);	
		if (flagA) flagB = BFS2(secondB, N - endd);
		
		// ���� ������ ���� ��� ����Ǿ������� ����� ����..
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