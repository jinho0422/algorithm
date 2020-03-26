/*
	https://www.acmicpc.net/problem/1944

	S, K에서 로봇이 복제되어 상하좌우 네 방향으로 움직이며, 로봇이열쇠가 있는 위치에 도달했을 때
	열쇠를 찾은 것으로 한다. 하나의 칸에 동시에 여러 개의 로봇이 위치할 수 있으며, 로봇이 한 번 지나간 자리라도 다른 로봇
	또는 자기 자신이 다시 지나갈 수 있다. 복제에는 시간이 들지 않으며, 로봇이 움직이는 횟수의 합은
	분열된 로봇이 각각이 움직인 횟수의 총 합을 말한다.
	각 복제된 로봇들이 키까지의 최소값을 vector에 넣어 MST를활용한 알고리즘 구현.
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
int parent[260];// 유니온 파인드를 쓰기위해..
int result;
bool flag;

typedef struct _pos {// 복제가 될 수 있는 곳의 행,열을 넣기 위한 struct
	int h, y;
}pos;
pos startKey[253];
int keyNum;

typedef struct _pos1 {// 로봇이 각각의 키에 도달할 수 있는 최단 거리를 넣는 struct
	int a, b, W;
}pos1;


bool cmp(const pos1 &p, const pos1 & q) { // MST를 사용하기 위한 Vector cmp
	return p.W < q.W;
}

vector<pos1> Vec;

void BFS(int hang, int yal);


int find_(int x) { // 유니온 파인드의 파인드를 하기 위한 함수..
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	int num = 3; // 복제될 수 있는 K 값의 복제 장소.

	scanf("%d %d", &N, &M);

	for (int i = 0; i <= 260; i++) {
		parent[i] = i;
	}
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
			if (board[hang][yal] == 'S' - '0') { // MST를 활용하기 위해서 복제될 수 있는 곳의 번호 매기기..
				board[hang][yal] = 2;
				startKey[keyNum++] = { hang, yal };
			}
			if (board[hang][yal] == 'K' - '0') {
				board[hang][yal] = num++;
				startKey[keyNum++] = { hang, yal };
			}
			
		}
	}

	for (int i = 0; i < keyNum; i++) {// BFS를 통해 다른 Key까지의 최단 거리 구하기 
		BFS(startKey[i].h, startKey[i].y);
		memset(check, false, sizeof(check));
	}

	sort(Vec.begin(), Vec.end(), cmp); // MST를 쓰기 윈한 정렬..
	int cnt = 0;
	for (int s = 0; s < Vec.size(); s++) {
		int a_head = find_(Vec[s].a);
		int b_head = find_(Vec[s].b);

		if (a_head != b_head) {// 유니온 파인트의 최고점이 다르면..
			parent[a_head] = b_head;
			result += Vec[s].W; // 결과값에 최단거리를 더해준다..
			cnt++;// 연결횟수 + 1
			if (cnt ==  M) { // 연결횟수가 키의 갯수와 같아지면 break.
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

				if (board[newY][newX] != 0 && !check[newY][newX]) {// 키값에 도달했을 때 vector에 각각의 로봇이 봇제될 수 있는 곳의 숫자와 최단거리를 넣어준다..
					check[newY][newX] = true;
					Vec.push_back(pos1({ board[hang][yal], board[newY][newX], time + 1 }));
				}
			}
		}
		time++;
	}
}