/*
	https://www.acmicpc.net/problem/1944

	S, K���� �κ��� �����Ǿ� �����¿� �� �������� �����̸�, �κ��̿��谡 �ִ� ��ġ�� �������� ��
	���踦 ã�� ������ �Ѵ�. �ϳ��� ĭ�� ���ÿ� ���� ���� �κ��� ��ġ�� �� ������, �κ��� �� �� ������ �ڸ��� �ٸ� �κ�
	�Ǵ� �ڱ� �ڽ��� �ٽ� ������ �� �ִ�. �������� �ð��� ���� ������, �κ��� �����̴� Ƚ���� ����
	�п��� �κ��� ������ ������ Ƚ���� �� ���� ���Ѵ�.
	�� ������ �κ����� Ű������ �ּҰ��� vector�� �־� MST��Ȱ���� �˰��� ����.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

int N, M;
char str[51];
int board[51][51];
bool check[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int parent[260];// ���Ͽ� ���ε带 ��������..
int result;
bool flag;

typedef struct _pos {// ������ �� �� �ִ� ���� ��,���� �ֱ� ���� struct
	int h, y;
}pos;
pos startKey[253];
int keyNum;

typedef struct _pos1 {// �κ��� ������ Ű�� ������ �� �ִ� �ִ� �Ÿ��� �ִ� struct
	int a, b, W;
}pos1;


bool cmp(const pos1 &p, const pos1 & q) { // MST�� ����ϱ� ���� Vector cmp
	return p.W < q.W;
}

vector<pos1> Vec;

void BFS(int hang, int yal);


int find_(int x) { // ���Ͽ� ���ε��� ���ε带 �ϱ� ���� �Լ�..
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	int num = 3; // ������ �� �ִ� K ���� ���� ���.

	scanf("%d %d", &N, &M);

	for (int i = 0; i <= 260; i++) {
		parent[i] = i;
	}
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
			if (board[hang][yal] == 'S' - '0') { // MST�� Ȱ���ϱ� ���ؼ� ������ �� �ִ� ���� ��ȣ �ű��..
				board[hang][yal] = 2;
				startKey[keyNum++] = { hang, yal };
			}
			if (board[hang][yal] == 'K' - '0') {
				board[hang][yal] = num++;
				startKey[keyNum++] = { hang, yal };
			}
			
		}
	}

	for (int i = 0; i < keyNum; i++) {// BFS�� ���� �ٸ� Key������ �ִ� �Ÿ� ���ϱ� 
		BFS(startKey[i].h, startKey[i].y);
		memset(check, false, sizeof(check));
	}

	sort(Vec.begin(), Vec.end(), cmp); // MST�� ���� ���� ����..
	int cnt = 0;
	for (int s = 0; s < Vec.size(); s++) {
		int a_head = find_(Vec[s].a);
		int b_head = find_(Vec[s].b);

		if (a_head != b_head) {// ���Ͽ� ����Ʈ�� �ְ����� �ٸ���..
			parent[a_head] = b_head;
			result += Vec[s].W; // ������� �ִܰŸ��� �����ش�..
			cnt++;// ����Ƚ�� + 1
			if (cnt ==  M) { // ����Ƚ���� Ű�� ������ �������� break.
				flag = true;
				break;
			}
		}
	}
	if(flag) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));
	int time = 0;

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) continue;

				if (board[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}

				if (board[newY][newX] != 0 && !check[newY][newX]) {// Ű���� �������� �� vector�� ������ �κ��� ������ �� �ִ� ���� ���ڿ� �ִܰŸ��� �־��ش�..
					check[newY][newX] = true;
					Vec.push_back(pos1({ board[hang][yal], board[newY][newX], time + 1 }));
				}
			}
		}
		time++;
	}
}