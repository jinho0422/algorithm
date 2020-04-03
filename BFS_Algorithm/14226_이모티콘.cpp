/*
	https://www.acmicpc.net/problem/14226
	
	priority_queue�� Ȱ���� BFS�� �̿��Ͽ� �˰��� ����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
bool check[1001][1001]; // 2���� check �迭�� ����� ������ ���� ���� �������� �� ���� Ŭ�����尡 ���� ���ִ����� �Ǵ��ؼ� �ֱ����ؼ��̴�.

typedef struct _pos { // s == ���� �̸�Ƽ�� ��, c == Ŭ�����忡 ����� �̸�Ƽ�� �� t == �ð�
	int s, c, t;
}pos;

struct cmp { // �ð��� ���� ������� queue���� �̱� ����..
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

void BFS(int start, int time);

int main() {
	scanf("%d", &N);
	BFS(1, 0);// ������ 1, �ð� 0�� �ʱⰪ���� BFS�Լ��� ����..
	return 0;
}

void BFS(int start, int time) {
	priority_queue<pos, vector<pos>, cmp> Q;
	Q.push(pos({ start, 0, time })); // priority_queue�� ������ 1, Ŭ�����忡 �ִ� �ʱ� �̸�Ƽ�� �� 0, �ð� 0

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (!check[p.c][p.s]) { // �ð��� �帧���� �������� �� ���� �̸�Ƽ���� ���� Ŭ�����忡 ����� �̸�Ƽ�� ���� �Ǵ�
			check[p.c][p.s] = true; // ���� check���� ���� �͸� Ȯ��..
			//printf("%d %d %d\n", p.s, p.c, p.t);
			if (p.s == N) { // ȭ�鿡 ����� ���� �̸�Ƽ���� �����̸�..
				printf("%d\n", p.t); // �ð� ���
				return;
			}

			if (p.c != 0 && p.s + p.c <= 1000) { // Ŭ�����忡 ����� �̸�Ƽ�� ������ 0�� �ƴϰ� ������ ������ Ŭ�����忡 ����� ���� ���� 1000���� �۰ų� ������
				Q.push(pos({ p.s + p.c, p.c, p.t + 1 }));
			}

			Q.push(pos({ p.s, p.s, p.t + 1 })); // Ŭ�����忡 ������ �̸�Ƽ�� ���� ����..

			if (p.s - 1 > 0) { // ������ �̸�Ƽ���� �������� �Ѱ��� �������� �� 0���� ũ��..
				Q.push(pos({ p.s - 1, p.c, p.t + 1 }));
			}
		}
	}
}