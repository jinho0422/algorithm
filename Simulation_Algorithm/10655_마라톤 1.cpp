/*
	https://www.acmicpc.net/problem/10655
	DFS를 이용하면 시간복잡도가 O(N^2)이므로 시간 초과가 난다. 효율성을 위해서
	우선 전체 길이를 구해놓고 시작하면 O(N)으로 줄일 수 있으므로
	하나를 건너뛸 때와 건너 뛰지 않을 때의 차를 구해서 이 중 가장 많이 줄일 수 있는 값을 찾아 
	전체 길이에서 빼주는 알고리즘 구현..
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
		startH = a; startY = b; // 다음값으로 이동하는 효과..
	}
	int skip = 0;
	for (int s = 1; s < N - 1; s++) { // 시작점과 마지막점을 빼고 
		pos prev = Vec[s - 1], cur = Vec[s], next = Vec[s + 1]; // 현재의 전, 현재, 현재의 다음 칸을 생각..
		int dist = abs(prev.h - cur.h) + abs(prev.y - cur.y) + abs(cur.h - next.h) + abs(cur.y - next.y); // 건너뛰지 않을 경우..
		int jump = abs(prev.h - next.h) + abs(prev.y - next.y); // 건너뛸경우..
		skip = max(skip, dist - jump); // 둘의 차이와 skip의 max값을 skip으로 갱신..
	}
	printf("%d\n", result - skip);
	return 0;
}

