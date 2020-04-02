/*
	https://www.acmicpc.net/problem/18233
	DFS + �ùķ��̼��� �̿��� �˰��� ����..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N, P, E;
bool check[21][1000001];
int tmp[21]; //ȸ����ȣ�� �ֱ� ���� �迭..
int result[21]; // ������� ���� �迭..
bool flag;

typedef struct _pos {// ȸ���� �������� ���ϴ� �ּҰ��� �ִ밪�� �ִ� struct
	int a, b;
}pos;
vector<pos> Vec;

void solve(int depth, int start);

int main() {
	scanf("%d %d %d", &N, &P, &E);
	for (int a, b, i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b })); // �ִ밪�� �ּҰ��� �ִ� Vec

	}

	solve(0, 0); // DFS
	if (!flag) printf("-1\n"); // �� �� ���� ����� -1
	else { // �� �� �ִ� ����� ���� ȸ���� ���� �� �ִ� �������� �� �� ���
		for (int i = 0; i < N; i++) {
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	return 0;
}

void solve(int depth, int start) {
	if (flag) return; // ������ �Ѱ��� ����ϱ� ����..

	if (depth == P) { // �� �� �ִ� ȸ���� �Ǹ�..
		memset(result, 0, sizeof(result)); // ������� �ʱ�ȭ..
		int sum = 0; // ��� E�� ã������ sum
		int min_sum = 0; // ȸ�� ������ ���ϴ� �ּ����� ���ϴ� sum
		int max_sum = 0; // ȸ�� ������ ���ϴ� �ִ����� ���ϴ� sum
		for (int i = 0; i < depth; i++) {
			result[tmp[i]] = Vec[tmp[i]].a;
			min_sum += Vec[tmp[i]].a;
			max_sum += Vec[tmp[i]].b;
			sum += result[tmp[i]];
		}

		if (min_sum <= E && max_sum >= E) { // ȸ�������� �ּҰ��� �ִ밪�� ���ϸ�

			for (int i = 0; i < depth; i++) { // ���õ� ȸ���� ���̿��� 
				int gap = Vec[tmp[i]].b - Vec[tmp[i]].a;
				if (sum + gap < E) { // ȸ���� �ִ�� �ּҸ� ���� sum�� ���Ѱ��� ��������� ������
					result[tmp[i]] += gap; // ȸ���� ������� �ٲ��ְ�
					sum += gap; // �ִ�� �ּ��� ���̸� sum�� �����ְ�
					continue;
				}
				if (sum + gap >= E) { // ���ų� ũ��
					result[tmp[i]] += (E - sum); //���ϴ� ��������� ���ݱ��� ������ sum�� ���� ȸ���� ������� ����..
					flag = true; // ������� �̷�ٴ� flag true..
					return;
				}
			}
		}
		return;
	}

	for (int s = start; s < Vec.size(); s++) { // �� �� �ִ� ȸ���� ���� �̴´�..(��������)
		tmp[depth] = s;
		solve(depth + 1, s + 1);
	}
}