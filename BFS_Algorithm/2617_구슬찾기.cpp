/*
	����� ������, ���԰� ��� �ٸ� N���� ������ �ִ�. N�� Ȧ���̸�, �������� ��ȣ�� 1,2,.... N���� �پ��ִ�.
	�� ���� �߿��� ���԰� ��ü�� �߰���(���� ������(N + 1) 2��°) ������ ã�� ���ؼ� �Ʒ��� ���� ���� �Ϸ����Ѵ�.
	�츮���� �־��� ���� ���� �����̴�. �� ���� ������ ��� ���� ������ ���ʿ� �ϳ��� �÷�����
	������� ���ſ�� �� �� �ִ�. �̷��� M���� ���� ��� ���� ���� ���￡ �÷��� ��� ���� ���ſ�� ��� �˾Ƴ´�.
	�� ����� �̿��Ͽ� ���԰� �߰��� �� ���ɼ��� ���� ���� �������� ���� �����Ѵ�.

	M ���� �ֿ� ���� ����� ���� ���԰� �߰��� ������ �� �� ���� ������ ������ ���ϴ� �˰����� �����ض�..

	�̸� �����ϱ� ���� BFS�� Ȱ���Ͽ� �ڽź��� ũ�Ⱑ ���� ����, �Ǵ� �ڽź��� ũ�Ⱑ ū ������ Ȯ���ϴ�
	�˰����� �����Ͽ� �Ǵ�..
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

vector<int> big_Vec[100]; // �ڽź��� ū ������ �ִ� vector
vector<int> small_Vec[100]; // �ڽź��� ���� ������ �ִ� vector

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
		if (!num_check[i]) { // �ڽ��� �߰� �������� ���� �𸣸�..
			memset(check, false, sizeof(check)); // check�迭 �ʱ�ȭ..
			big_BFS(i);// �ڽź��� ū ������ ����� �Ǵ��ϱ� ���� BFS..
		}
		if (!num_check[i]) {
			memset(check, false, sizeof(check)); // check�迭 �ʱ�ȭ..
			small_BFS(i); // �ڽź��� ���� ������ ����� �Ǵ��ϱ� ���� BFS..
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
				if (num > N / 2) { // �ڽź��� ū ������ ��ü�� ������ �ݺ��� ������ �߰� ������ �� �� �����Ƿ�
					cnt++; // ����� + 1
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
				if (num > N / 2) { // �ڽź��� ���� ������ ��ü ������ �ݺ��� ������ �߰� ������ �� �� �����Ƿ�..
					cnt++; // ����� + 1
					num_check[start] = true;
					return;
				}
				Q.push(first);
			}
		}
	}
}