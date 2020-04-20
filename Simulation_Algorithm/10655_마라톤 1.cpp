/*
	https://www.acmicpc.net/problem/10655
	DFS�� �̿��ϸ� �ð����⵵�� O(N^2)�̹Ƿ� �ð� �ʰ��� ����. ȿ������ ���ؼ�
	�켱 ��ü ���̸� ���س��� �����ϸ� O(N)���� ���� �� �����Ƿ�
	�ϳ��� �ǳʶ� ���� �ǳ� ���� ���� ���� ���� ���ؼ� �� �� ���� ���� ���� �� �ִ� ���� ã�� 
	��ü ���̿��� ���ִ� �˰��� ����..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

int N;
int result;
int a, b;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec;


int main() {
	scanf("%d", &N);
	scanf("%d %d", &a, &b);
	Vec.push_back(pos({ a, b }));
	int startH = Vec[0].h; 
	int startY = Vec[0].y;
	for (int s = 0; s < N - 1; s++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b }));
		result += (abs(startH - a) + abs(startY - b));
		startH = a; startY = b; // ���������� �̵��ϴ� ȿ��..
	}
	int skip = 0;
	for (int s = 1; s < N - 1; s++) { // �������� ���������� ���� 
		pos prev = Vec[s - 1], cur = Vec[s], next = Vec[s + 1]; // ������ ��, ����, ������ ���� ĭ�� ����..
		int dist = abs(prev.h - cur.h) + abs(prev.y - cur.y) + abs(cur.h - next.h) + abs(cur.y - next.y); // �ǳʶ��� ���� ���..
		int jump = abs(prev.h - next.h) + abs(prev.y - next.y); // �ǳʶ۰��..
		skip = max(skip, dist - jump); // ���� ���̿� skip�� max���� skip���� ����..
	}
	printf("%d\n", result - skip);
	return 0;
}

